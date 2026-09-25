#include "DxLib.h"
#include "CheckObstacle.h"
#include "../CharacterBase.h"
#include "../../MyMath/MyMath.h"
#include "../../Map/MapManager.h"

const float OBSTACLE_SEARCH_LENGTH = 20.0f;

namespace CheckObstacle
{
	// Characterの場合
	MV1_COLL_RESULT_POLY CheckObstacleTargetCharacter(CharacterBase* thisCharacter, CharacterBase* target)
	{
		VECTOR thisPos = thisCharacter->GetPos();
		float thisRadius = thisCharacter->GetRadius();

		VECTOR targetPos = target->GetPos();
		float targetRadius = target->GetRadius();

		return CheckObstacleTarget(thisPos, thisRadius, targetPos, targetRadius);
	}

	// Rooterの場合
	MV1_COLL_RESULT_POLY CheckObstacleTargetRooter(Rooter* thisRooter, CharacterBase* target)
	{
		VECTOR thisPos = thisRooter->GetPos();
		float thisRadius = thisRooter->GetRadius();

		VECTOR targetPos = target->GetPos();
		float targetRadius = target->GetRadius();

		return CheckObstacleTarget(thisPos, thisRadius, targetPos, targetRadius);
	}

	MV1_COLL_RESULT_POLY CheckObstacleTarget(VECTOR thisPos, float thisRadius, VECTOR targetPos, float targetRadius)
	{
		// 自身の中心
		VECTOR thisCenter = MyMath::VecAdd(thisPos, MyMath::VecY(thisRadius));

		// ターゲットの中心
		VECTOR targetCenter = MyMath::VecAdd(targetPos, MyMath::VecY(targetRadius));

		VECTOR toTarget = MyMath::VecCreate(thisCenter, targetCenter);
		VECTOR toTargetNormal = VNorm(toTarget);

		// ターゲットに向けてのベクトル
		VECTOR targetDir = MyMath::VecCreate(thisCenter, targetCenter);
		float targetDistance = VSize(targetDir);

		VECTOR targetDirNormal = VNorm(targetDir);

		VECTOR rayEnd = MyMath::VecZero();

		VECTOR ray = MyMath::VecScale(targetDirNormal, OBSTACLE_SEARCH_LENGTH * 2);
		rayEnd = MyMath::VecAdd(thisCenter, ray);

		int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();

		DxLib::DrawLine3D(thisCenter, targetCenter, COLOR_RED);

		return MV1CollCheck_Line(mapCollisionHandle, -1, thisCenter, targetCenter);
	}


	MV1_COLL_RESULT_POLY_DIM CheckObstacleForwardCharacter(CharacterBase* thisCharacter, bool isRight)
	{
		VECTOR pos = thisCharacter->GetPos();
		VECTOR rot = thisCharacter->GetRot();
		float radius = thisCharacter->GetRadius();

		return CheckObstacleForward(pos, rot, radius, isRight);
	}

	MV1_COLL_RESULT_POLY_DIM CheckObstacleForwardRooter(Rooter* thisRooter, bool isRight)
	{
		VECTOR thisPos = thisRooter->GetPos();
		VECTOR thisRot = thisRooter->GetRot();
		float thisRadius = thisRooter->GetRadius();

		return CheckObstacleForward(thisPos, thisRot, thisRadius, isRight);
	}

	MV1_COLL_RESULT_POLY_DIM CheckObstacleForward(VECTOR pos, VECTOR rot, float radius, bool isRight)
	{
		// 自身の中心
		VECTOR thisCenter = MyMath::VecAdd(pos, MyMath::VecY(radius));

		VECTOR forward = VGet(sinf(rot.y), 0.0f, cosf(rot.y));
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

		VECTOR rayStart = VAdd(thisCenter, VScale(VNorm(centerToSide), radius * 1.2f));

		VECTOR rayEnd = VAdd(rayStart, VScale(forwardNormal, OBSTACLE_SEARCH_LENGTH));

		int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();
		DxLib::DrawLine3D(rayStart, rayEnd, COLOR_BLUE);

		return MV1CollCheck_LineDim(mapCollisionHandle, -1, rayStart, rayEnd);
	}

	ForwardResult GetForwardResult(MV1_COLL_RESULT_POLY_DIM coll)
	{
		ForwardResult result = {};
		result.normal = MyMath::VecZero();
		result.isHit = false;
		if (coll.HitNum > 0)
		{
			for (int i = 0; i < coll.HitNum; i++)
			{
				if (coll.Dim[i].Normal.y < 0.7f)
				{
					MV1_COLL_RESULT_POLY* poly = &coll.Dim[i];

					if (poly != nullptr)
					{
						result.normal = poly->Normal;
						result.isHit = true;
						break;
					}
				}
			}
		}

		return result;
	}
}