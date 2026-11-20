#include "CharacterAI.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../Managers/CharacterManager/CharacterManager.h"
#include "../../MyColor/MyColor.h"
#include "../../Managers/MapManager/MapManager.h"
#include "../../Scene/SceneManager.h"
#include <cmath>

constexpr float OBSTACLE_SEARCH_LENGTH = 20.0f;
constexpr float NODE_ARCHIVE_DISTANCE = 5.0f; // ノードに到達したと判定される距離

CharacterAI::CharacterAI(GameObject* owner)
	: Component(owner)
	, m_MoveType(AI_MOVE_NONE)
	, m_PrevMoveType(AI_MOVE_NONE)
	, m_ActiveNodePos(MyMath::VecZero())
	, m_SearchNode(false)
{
	for (int i = 0; i < AI_MOVE_MAX; i++)
	{
		m_StateFunc[i] = nullptr;
	}
}

CharacterAI::~CharacterAI()
{

}

void CharacterAI::Start()
{
	m_MoveType = AI_MOVE_TRACK;

	m_Parameter = m_Owner->GetComponent<CharacterParameter>();
	m_Physics = m_Owner->GetComponent<Physics3D>();
	m_Input = m_Owner->GetComponent<NPCInput>();

	// マップのノードを取得
	std::shared_ptr<GameObject> currentMap = MapManager::GetInstance()->GetCurrentMap().lock();
	if (currentMap)
	{
		std::shared_ptr<MapNode> mapNode = currentMap->GetComponent<MapNode>();
		m_NodeData = mapNode->GetNodeData();
	}

	m_StateFunc[AI_MOVE_TRACK] = &CharacterAI::Track;
	m_StateFunc[AI_MOVE_AVOID_OBSTACLE] = &CharacterAI::AvoidObstacle;
	m_StateFunc[AI_MOVE_ATTACK] = &CharacterAI::Attack;
	m_StateFunc[AI_MOVE_ESCAPE] = &CharacterAI::Escape;
	m_StateFunc[AI_MOVE_GET_ITEM] = &CharacterAI::GetItem;
}

void CharacterAI::Step()
{
	m_PrevMoveType = m_MoveType;

	(this->*m_StateFunc[m_MoveType])();

	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	MV1_COLL_RESULT_POLY_DIM ray = CheckObstacleTarget();

	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	VECTOR moveDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	VECTOR moveDirNormal = VNorm(moveDir);
	float distance = VSize(moveDir);

	if (ray.HitNum > 0)
	{
		m_MoveType = AI_MOVE_AVOID_OBSTACLE;

		// 回避モードに入ったフレームはノード探索
		if (m_PrevMoveType != AI_MOVE_AVOID_OBSTACLE)
		{
			m_SearchNode = true;
		}
	}
	else if (distance < sharedPtrs.parameterShared->GetAttackRange())
	{
		m_MoveType = AI_MOVE_ATTACK;
	}
	else
	{
		m_MoveType = AI_MOVE_TRACK;
	}
}

/// <summary>
/// ターゲットに接近
/// </summary>
void CharacterAI::Track()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	SearchTarget();

	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	VECTOR targetPos = MyMath::VecZero();

	VECTOR moveDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	VECTOR moveDirNormal = VNorm(moveDir);

	sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(moveDirNormal.x * 1000.0f));
	sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(-moveDirNormal.z * 1000.0f));
}

/// <summary>
/// 障害物回避
/// </summary>
void CharacterAI::AvoidObstacle()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	if (m_NodeData.empty()) return;

	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(sharedPtrs.physicsShared->GetPos(), MyMath::VecY(sharedPtrs.physicsShared->GetScale().y / 2.0f));

	float vecDotMax = -1.0f;

	if (m_SearchNode)
	{
		for (VECTOR nodePos : m_NodeData)
		{
			MV1_COLL_RESULT_POLY_DIM ray = CheckObstaclePos(thisCenter, nodePos);

			if (ray.HitNum > 0) continue;

			VECTOR thisToTarget = MyMath::VecCreate(thisCenter, targetPhysicsShared->GetPos());
			VECTOR thisToNode = MyMath::VecCreate(thisCenter, nodePos);
			thisToTarget.y = 0.0f;
			thisToNode.y = 0.0f;
			VECTOR thisToTargetNorm = VNorm(thisToTarget);
			VECTOR thisToNodeNorm = VNorm(thisToNode);

			float dot = VDot(thisToTargetNorm, thisToNodeNorm);

			if (dot > vecDotMax)
			{
				m_ActiveNodePos = nodePos;
				vecDotMax = dot;
			}
		}

		m_SearchNode = false;
	}

	VECTOR toActiveNode = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), m_ActiveNodePos);
	toActiveNode.y = 0.0f;
	
	// 目標のノードに到着したら次のノードを探索
	if (VSize(toActiveNode) < NODE_ARCHIVE_DISTANCE)
	{
		m_SearchNode = true;
	}

	VECTOR moveDirNormal = VNorm(toActiveNode);

	sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(moveDirNormal.x * 1000.0f));
	sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(-moveDirNormal.z * 1000.0f));
}

/// <summary>
/// 攻撃
/// </summary>
void CharacterAI::Attack()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	SearchTarget();

	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	VECTOR moveDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	float distance = VSize(moveDir);

	float currentDirY = sharedPtrs.physicsShared->GetDirAngleY();
	VECTOR currentDir = VGet(sinf(currentDirY), 0.0f, cosf(currentDirY));
	currentDir = VNorm(currentDir);

	VECTOR targetDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	targetDir.y = 0.0f;
	targetDir = VNorm(targetDir);

	// ターゲットの方を向き直す
	if (currentDir.x == targetDir.x && currentDir.z == targetDir.z)
	{
		sharedPtrs.inputShared->InputLeftStickX(0);
		sharedPtrs.inputShared->InputLeftStickY(0);
	}
	else
	{
		sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(targetDir.x * 1000.0f));
		sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(-targetDir.z * 1000.0f));
	}

	if (sharedPtrs.parameterShared->ActionAble())
	{
		sharedPtrs.inputShared->TriggerButton(TRIGGER_ATTACK);
	}
}

/// <summary>
/// 逃走
/// </summary>
void CharacterAI::Escape()
{

}

/// <summary>
/// アイテムを取りに行く
/// </summary>
void CharacterAI::GetItem()
{

}

/// <summary>
/// 最も近い敵を探す
/// </summary>
void CharacterAI::SearchTarget()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	auto characters = CharacterManager::GetInstance()->GetCharacters();

	float nearestDistance = 10000.0f;

	std::shared_ptr<Physics3D> nearestPhysics = nullptr;
	std::shared_ptr<CharacterParameter> nearestParameter = nullptr;

	for (auto& target : characters)
	{
		auto targetShared = target.lock();

		if (!targetShared) continue;

		std::shared_ptr<CharacterParameter> targetParameter = targetShared->GetComponent<CharacterParameter>();
		std::shared_ptr<Physics3D> targetPhysics = targetShared->GetComponent<Physics3D>();

		if (sharedPtrs.parameterShared->IsBoss() == targetParameter->IsBoss()) continue;
		if (targetParameter->GetAction() == ACTION_DIE)continue;

		VECTOR thisToTarget = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysics->GetPos());
		float thisDistance = VSize(thisToTarget);

		if (thisDistance < nearestDistance)
		{
			nearestDistance = thisDistance;
			nearestPhysics = targetPhysics;
			nearestParameter = targetParameter;
		}
	}

	if (nearestPhysics != nullptr && nearestParameter != nullptr)
	{
		m_TargetData.physics = nearestPhysics;
		m_TargetData.parameter = nearestParameter;
	}
}

/// <summary>
/// 自身からターゲットへ障害物探索
/// </summary>
/// <returns>衝突情報</returns>
MV1_COLL_RESULT_POLY_DIM CharacterAI::CheckObstacleTarget()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety)
	{
		MV1_COLL_RESULT_POLY_DIM coll{};
		return coll;
	}

	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(sharedPtrs.physicsShared->GetPos(), MyMath::VecY(sharedPtrs.physicsShared->GetScale().y / 2.0f));

	auto targetPhysicShared = m_TargetData.physics.lock();

	// ターゲットの中心
	VECTOR targetCenter = MyMath::VecAdd(targetPhysicShared->GetPos(), MyMath::VecY(targetPhysicShared->GetScale().y / 2.0f));

	return CheckObstaclePos(thisCenter, targetCenter);
}

/// <summary>
/// 自身から指定した座標へ障害物探索
/// </summary>
/// <returns>衝突情報</returns>
MV1_COLL_RESULT_POLY_DIM CharacterAI::CheckObstaclePos(VECTOR thisPos, VECTOR targetPos)
{
	MV1_COLL_RESULT_POLY_DIM coll{};

	auto mapObjShared = MapManager::GetInstance()->GetCurrentMap().lock();

	if (!mapObjShared) return coll;

	int mapCollisionHandle = mapObjShared->GetComponent<MeshCollision>()->GetCollisionHandle();

	if (mapCollisionHandle == -1) return coll;

#ifdef _DEBUG
	DxLib::DrawLine3D(thisPos, targetPos, COLOR_GREEN);
#endif

	return MV1CollCheck_LineDim(mapCollisionHandle, -1, thisPos, targetPos);

	return coll;
}

/// <summary>
/// メンバ変数の安全チェック
/// </summary>
/// <returns>SharedPointerの構造体</returns>
CharacterAI::SharedMembers CharacterAI::CheckMemberPtrs()
{
	CharacterAI::SharedMembers ptrs;

	ptrs.inputShared = m_Input.lock();
	ptrs.parameterShared = m_Parameter.lock();
	ptrs.physicsShared = m_Physics.lock();

	if (!ptrs.inputShared || !ptrs.parameterShared || !ptrs.physicsShared)
	{
		ptrs.isSafety = false;
	}
	else
	{
		ptrs.isSafety = true;
	}

	return ptrs;
}