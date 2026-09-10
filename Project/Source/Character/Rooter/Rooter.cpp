#include "Rooter.h"
#include "../../MyMath/MyMath.h"
#include "../CharacterBase.h"
#include "../../Map/MapManager.h"
#include "DxLib.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionSphere.h"

const float ROOTER_MOVE_SPEED = 3.0f;
const float ROOTER_OBSTACLE_SEARCH_LENGTH = 20.0f;
const int ROOTER_DIRECTION_CHANGE_INTERVAL = 10;
const float TARGET_HIT_DISTANCE = 5.0f;
const int LIFE_TIMELIMIT = 30 * 60;

Rooter::Rooter()
{
	m_Pos = MyMath::VecZero();
	m_PrevPos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_MoveDir = MyMath::VecZero();
	m_Move = MyMath::VecZero();

	m_DirectionChangeTimer = 0;
	m_LifeTimer = 0;

	m_Radius = 0.0f;
	m_Speed = 0.0f;

	m_AvoidRight = false;
	m_Active = false;

	m_Sphere = nullptr;
	m_Target = nullptr;
	m_Parent = nullptr;
	m_Pair = nullptr;
}

Rooter::~Rooter()
{
	Fin();
}

void Rooter::Init()
{

}

void Rooter::Start()
{
	m_Active = true;

	m_LifeTimer = LIFE_TIMELIMIT;

	m_Speed = ROOTER_MOVE_SPEED;

	m_DirectionChangeTimer = ROOTER_DIRECTION_CHANGE_INTERVAL;

	m_Pos = m_Parent->GetPos();
	m_Radius = m_Parent->GetRadius();

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, m_Radius, 0.0f));
	m_Sphere->SetRadius(m_Radius);
}

void Rooter::Step()
{
	VECTOR targetPos = MyMath::VecZero();

	m_LifeTimer--;

	if (m_LifeTimer <= 0)
	{
		m_Active = false;
		m_Pair->SetActive(false);
	}

	if (m_Target != nullptr)
	{
		targetPos = m_Target->GetPos();
	}

	VECTOR distance = MyMath::VecCreate(m_Pos, targetPos);
	if (VSize(distance) < TARGET_HIT_DISTANCE)
	{
		m_Parent->SetAvoidRight(m_AvoidRight);
		m_Active = false;
		m_Pair->SetActive(false);
		CharacterManager::GetInstance()->SetInactiveOlder(this);
	}

	// 移動
	VECTOR toTarget = MyMath::VecZero();

	if (m_Target != nullptr)
	{
		m_DirectionChangeTimer--;

		VECTOR obstacleNormal = MyMath::VecZero();
		bool hitObstacle = false;

		toTarget = MyMath::VecCreate(m_Pos, targetPos);

		if (m_DirectionChangeTimer <= 0)
		{
			// 自身の右端と左端から前方に向けて障害物検知（引っかかりを防ぐ）
			MV1_COLL_RESULT_POLY_DIM checkObstacleRight = CheckObstacleForward(true);
			MV1_COLL_RESULT_POLY_DIM checkObstacleLeft = CheckObstacleForward(false);

			// 右端からの判定
			if (checkObstacleRight.HitNum > 0)
			{
				for (int i = 0; i < checkObstacleRight.HitNum; i++)
				{
					if (checkObstacleRight.Dim[i].Normal.y < 0.7f)
					{
						MV1_COLL_RESULT_POLY* poly = &checkObstacleRight.Dim[i];

						if (poly != nullptr)
						{
							obstacleNormal = poly->Normal;
							hitObstacle = true;
							break;
						}
					}
				}
			}
			// 左端からの判定
			else if (checkObstacleLeft.HitNum > 0)
			{
				for (int i = 0; i < checkObstacleLeft.HitNum; i++)
				{
					if (checkObstacleLeft.Dim[i].Normal.y < 0.7f)
					{
						MV1_COLL_RESULT_POLY* poly = &checkObstacleLeft.Dim[i];

						if (poly != nullptr)
						{
							obstacleNormal = poly->Normal;
							hitObstacle = true;
							break;
						}
					}
				}
			}

			MV1CollResultPolyDimTerminate(checkObstacleRight);
			MV1CollResultPolyDimTerminate(checkObstacleLeft);

			// 障害物があれば迂回
			if (hitObstacle)
			{
				m_DirectionChangeTimer = ROOTER_DIRECTION_CHANGE_INTERVAL;

				if (m_AvoidRight)
				{
					m_MoveDir = VCross(obstacleNormal, MyMath::VecY(1.0f));
				}
				else
				{
					m_MoveDir = VCross(obstacleNormal, MyMath::VecY(-1.0f));
				}
			}
			else
			{
				m_MoveDir = toTarget;
			}
		}

		float targetDistance = MyMath::VecLong(toTarget);

		VECTOR moveDirNormal = MyMath::VecNormarize(m_MoveDir);

		if (m_Target != nullptr)
		{
			m_Rot.y = atan2f(moveDirNormal.x, moveDirNormal.z);

			m_Move.x = m_Speed * moveDirNormal.x;
			m_Move.z = m_Speed * moveDirNormal.z;
		}
	}
}

void Rooter::Update()
{
	m_PrevPos = m_Pos;

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;
}

void Rooter::Draw()
{
	int index = m_Parent->GetIndex();
	unsigned int color = GetColor(0, 0, 0);
	if (index == 0)
	{
		color = GetColor(255, 0, 0);
	}
	if (index == 1)
	{
		color = GetColor(0, 255, 0);
	}
	if (index == 2)
	{
		color = GetColor(0, 0, 255);
	}
	//DrawSphere3D(VAdd(m_Sphere->GetTargetPos(),m_Sphere->GetLocalPos()), m_Radius, 16, color, GetColor(255, 255, 255), TRUE);
}

void Rooter::Fin()
{

}

MV1_COLL_RESULT_POLY Rooter::CheckObstacleTarget()
{
	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(m_Pos, MyMath::VecY(m_Radius));

	// ターゲットの中心
	VECTOR targetCenter = MyMath::VecAdd(m_Target->GetPos(), MyMath::VecY(m_Target->GetRadius()));

	VECTOR toTarget = MyMath::VecCreate(thisCenter, targetCenter);
	VECTOR toTargetNormal = VNorm(toTarget);

	// ターゲットに向けてのベクトル
	VECTOR targetDir = MyMath::VecCreate(thisCenter, targetCenter);
	float targetDistance = VSize(targetDir);

	VECTOR targetDirNormal = VNorm(targetDir);

	VECTOR rayEnd = MyMath::VecZero();

	// ターゲットが遠い場合
	if (targetDistance > ROOTER_OBSTACLE_SEARCH_LENGTH * 2)
	{
		VECTOR ray = MyMath::VecScale(targetDirNormal, ROOTER_OBSTACLE_SEARCH_LENGTH * 2);
		rayEnd = MyMath::VecAdd(thisCenter, ray);
	}
	// ターゲットが近い場合
	else
	{
		rayEnd = targetCenter;
	}

	int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();

#ifdef DEBUG
	//DrawLine3D(thisCenter, rayEnd, GetColor(255, 0, 0));
#endif

	return MV1CollCheck_Line(mapCollisionHandle, -1, thisCenter, rayEnd);
}

MV1_COLL_RESULT_POLY_DIM Rooter::CheckObstacleForward(bool isRight)
{
	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(m_Pos, MyMath::VecY(m_Radius));

	VECTOR forward = VGet(sinf(m_Rot.y), 0.0f, cosf(m_Rot.y));
	VECTOR forwardNormal = VNorm(forward);

	VECTOR centerToSide = MyMath::VecZero();

	// 右端
	if (isRight)
	{
		centerToSide = VGet(-forwardNormal.z, 0.0f, forwardNormal.x);
	}
	// 左端
	else
	{
		centerToSide = VGet(forwardNormal.z, 0.0f, -forwardNormal.x);
	}

	VECTOR rayStart = VAdd(thisCenter, VScale(VNorm(centerToSide), m_Radius));

	VECTOR rayEnd = VAdd(rayStart, VScale(forwardNormal, ROOTER_OBSTACLE_SEARCH_LENGTH));

	int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();

#ifdef DEBUG
	//DrawLine3D(rayStart, rayEnd, GetColor(0, 0, 255));
#endif

	return MV1CollCheck_LineDim(mapCollisionHandle, -1, rayStart, rayEnd);
}

void Rooter::HitStage(MapBase* map)
{
	float thisRadius = m_Sphere->GetRadius();

	MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(m_Sphere->GetWorldPos(), m_Sphere->GetRadius());

	for (int i = 0; i < hitResult.HitNum; i++)
	{
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];

		float slope = polygon.Normal.y;
		float hitHeight = polygon.HitPosition.y;

		float hitHeightDiff = fabsf(hitHeight - m_Pos.y);

		if (polygon.Normal.y <= 0.1f)
		{
			if (hitHeightDiff >= 6.0f)
			{
				if (polygon.Normal.x * polygon.Normal.x <= 0.1f)
				{
					m_Pos.z = m_PrevPos.z;
					m_Move.z = 0.0f;
				}
				if (polygon.Normal.z * polygon.Normal.z <= 0.1f)
				{
					m_Pos.x = m_PrevPos.x;
					m_Move.x = 0.0f;
				}
				continue;
			}
		}

		VECTOR spherePos = m_Sphere->GetWorldPos();
		VECTOR lineStart = spherePos;
		VECTOR lineEnd = spherePos;

		lineStart.y += thisRadius;
		lineEnd.y -= thisRadius * 2.0f;

		HITRESULT_LINE lineResult = HitCheck_Line_Triangle(
			lineStart, lineEnd, polygon.Position[0], polygon.Position[1],
			polygon.Position[2]);

		if (!lineResult.HitFlag) continue;

		m_Pos.y = lineResult.Position.y;

		m_Move.y = 0.0f;
	}
}