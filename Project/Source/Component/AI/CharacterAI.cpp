#include "CharacterAI.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../Managers/CharacterManager/CharacterManager.h"
#include "../../MyColor/MyColor.h"
#include "../../Map/MapManager.h"

const float OBSTACLE_SEARCH_LENGTH = 20.0f;

CharacterAI::CharacterAI(GameObject* owner) : Component(owner)
{
	m_MoveType = AI_MOVE_NONE;
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
}

void CharacterAI::Step()
{
	switch (m_MoveType)
	{
	case AI_MOVE_TRACK:
		Track();
		break;
	case AI_MOVE_AVOID_OBSTACLE:
		AvoidObstacle();
		break;
	case AI_MOVE_ATTACK:
		Attack();
		break;
	case AI_MOVE_ESCAPE:
		Escape();
		break;
	case AI_MOVE_MAX:
		break;
	case AI_MOVE_NONE:
		break;
	default:
		break;
	}

	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	MV1_COLL_RESULT_POLY_DIM targetRight = CheckObstacleTarget(true);
	MV1_COLL_RESULT_POLY_DIM targetLeft = CheckObstacleTarget(false);

	MV1_COLL_RESULT_POLY_DIM forwardRight = CheckObstacleForward(true);
	MV1_COLL_RESULT_POLY_DIM forwardLeft = CheckObstacleForward(false);


	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	VECTOR moveDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	VECTOR moveDirNormal = VNorm(moveDir);
	float distance = VSize(moveDir);

	if (distance < sharedPtrs.parameterShared->GetAttackRange())
	{
		m_MoveType = AI_MOVE_ATTACK;
	}
	else if ((forwardLeft.HitNum > 0 || forwardRight.HitNum > 0)
		&& (targetLeft.HitNum > 0 || targetRight.HitNum > 0))
	{
		m_MoveType = AI_MOVE_AVOID_OBSTACLE;
	}
	else
	{
		m_MoveType = AI_MOVE_TRACK;
	}
}

void CharacterAI::Track()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	SearchTarget();

	auto targetParameterShared = m_TargetData.parameter.lock();
	auto targetPhysicsShared = m_TargetData.physics.lock();

	if (!targetParameterShared || !targetPhysicsShared) return;

	VECTOR moveDir = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysicsShared->GetPos());
	VECTOR moveDirNormal = VNorm(moveDir);
	float distance = VSize(moveDir);

	sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(moveDirNormal.x * 1000.0f));
	sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(-moveDirNormal.z * 1000.0f));
}

void CharacterAI::AvoidObstacle()
{
	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	MV1_COLL_RESULT_POLY_DIM forwardRight = CheckObstacleForward(true);
	MV1_COLL_RESULT_POLY_DIM forwardLeft = CheckObstacleForward(false);

	if (forwardRight.Dim == nullptr || forwardRight.Dim) return;

	if (forwardLeft.HitNum > 0)
	{
		VECTOR obstacleNormal = forwardRight.Dim->Normal;
		VECTOR avoidDir = VGet(obstacleNormal.z, 0.0, obstacleNormal.x);

		sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(avoidDir.x * 1000.0f));
		sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(avoidDir.z * 1000.0f));
	}
	else if (forwardLeft.HitNum > 0)
	{
		VECTOR obstacleNormal = forwardLeft.Dim->Normal;
		VECTOR avoidDir = VGet(obstacleNormal.z, 0.0, obstacleNormal.x);

		sharedPtrs.inputShared->InputLeftStickX(static_cast<int>(avoidDir.x * 1000.0f));
		sharedPtrs.inputShared->InputLeftStickY(static_cast<int>(avoidDir.z * 1000.0f));
	}
}

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

	if (distance > sharedPtrs.parameterShared->GetAttackRange())
	{
		m_MoveType = AI_MOVE_TRACK;
	}

	if (sharedPtrs.parameterShared->ActionAble())
	{
		sharedPtrs.inputShared->TriggerButton(TRIGGER_ATTACK);
	}

	sharedPtrs.inputShared->InputLeftStickX(0);
	sharedPtrs.inputShared->InputLeftStickY(0);
}

void CharacterAI::Escape()
{

}

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

		VECTOR thisToTarget = MyMath::VecCreate(sharedPtrs.physicsShared->GetPos(), targetPhysics->GetPos());
		float thisDistance = VSize(thisToTarget);

		if (thisDistance < nearestDistance)
		{
			nearestPhysics = targetPhysics;
			nearestParameter = targetParameter;
		}
	}

	m_TargetData.physics = nearestPhysics;
	m_TargetData.parameter = nearestParameter;
}

MV1_COLL_RESULT_POLY_DIM CharacterAI::CheckObstacleForward(bool isRight)
{
	MV1_COLL_RESULT_POLY_DIM coll{};

	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return coll;

	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(sharedPtrs.physicsShared->GetPos(), MyMath::VecY(sharedPtrs.physicsShared->GetScale().y / 2.0f));

	VECTOR forward = sharedPtrs.physicsShared->GetForward();

	VECTOR centerToSide = MyMath::VecZero();

	// 左端
	if (isRight)
	{
		centerToSide = VGet(forward.z, 0.0f, -forward.x);
	}
	// 右端
	else
	{
		centerToSide = VGet(-forward.z, 0.0f, forward.x);
	}

	VECTOR rayStart = VAdd(thisCenter, VScale(VNorm(centerToSide), sharedPtrs.physicsShared->GetScale().y / 2.0f * 1.2f));

	VECTOR rayEnd = VAdd(rayStart, VScale(forward, OBSTACLE_SEARCH_LENGTH));

	auto mapObjShared = MapManager::GetInstance()->GetCurrentMap().lock();

	if (!mapObjShared) return coll;

	int mapCollisionHandle = mapObjShared->GetComponent<MeshCollision>()->GetCollisionHandle();

	if (mapCollisionHandle == -1) return coll;

	if (isRight)
	{
		DxLib::DrawLine3D(rayStart, rayEnd, COLOR_RED);
	}
	else
	{
		DxLib::DrawLine3D(rayStart, rayEnd, COLOR_BLUE);
	}

	coll = MV1CollCheck_LineDim(mapCollisionHandle, -1, rayStart, rayEnd);

	return coll;
}

MV1_COLL_RESULT_POLY_DIM CharacterAI::CheckObstacleTarget(bool isRight)
{
	MV1_COLL_RESULT_POLY_DIM coll{};

	CharacterAI::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return coll;

	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(sharedPtrs.physicsShared->GetPos(), MyMath::VecY(sharedPtrs.physicsShared->GetScale().y / 2.0f));

	VECTOR forward = sharedPtrs.physicsShared->GetForward();

	VECTOR centerToSide = MyMath::VecZero();

	// 左端
	if (isRight)
	{
		centerToSide = VGet(forward.z, 0.0f, -forward.x);
	}
	// 右端
	else
	{
		centerToSide = VGet(-forward.z, 0.0f, forward.x);
	}

	auto targetPhysicShared = m_TargetData.physics.lock();

	// ターゲットの中心
	VECTOR targetCenter = MyMath::VecAdd(targetPhysicShared->GetPos(), MyMath::VecY(targetPhysicShared->GetScale().y / 2.0f));

	VECTOR toTarget = MyMath::VecCreate(thisCenter, targetCenter);
	VECTOR toTargetNormal = VNorm(toTarget);

	VECTOR rayStart = VAdd(thisCenter, VScale(VNorm(centerToSide), sharedPtrs.physicsShared->GetScale().y / 2.0f * 1.2f));

	VECTOR rayEnd = VAdd(rayStart, VScale(forward, OBSTACLE_SEARCH_LENGTH));

	auto mapObjShared = MapManager::GetInstance()->GetCurrentMap().lock();

	if (!mapObjShared) return coll;

	int mapCollisionHandle = mapObjShared->GetComponent<MeshCollision>()->GetCollisionHandle();

	if (mapCollisionHandle == -1) return coll;

	DxLib::DrawLine3D(rayStart, targetCenter, COLOR_GREEN);

	return MV1CollCheck_LineDim(mapCollisionHandle, -1, rayStart, targetCenter);

	return coll;
}

void CharacterAI::CreateRooter(bool isRight)
{
	auto rooterObj = std::make_shared<GameObject>();

	auto rooterPhysics = rooterObj->AddComponent<Physics3D>();
	auto rooterAI = rooterObj->AddComponent<CharacterAI>();

	m_Rooters.push_back(rooterObj);
}

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