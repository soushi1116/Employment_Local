#pragma once

#include "DxLib.h"
#include <variant>
#include "../../MyMath/MyMath.h"
#include "../CharacterBase.h"
#include "../Rooter/Rooter.h"
#include "../../Map/MapManager.h"
#include "../../MyColor/MyColor.h"

namespace CheckObstacle
{
	const float OBSTACLE_SEARCH_LENGTH = 20.0f;

	inline MV1_COLL_RESULT_POLY CheckObstacleTarget(const std::variant<CharacterBase*, Rooter*>& thisCharacter, CharacterBase* target)
	{
		VECTOR thisPos = MyMath::VecZero();
		float thisRadius = 0.0f;

		std::visit([&](auto* character)
			{
				if (character != nullptr)
				{
					thisPos = character->GetPos();
					thisRadius = character->GetRadius();
				}
			}, thisCharacter);

		VECTOR targetPos = target->GetPos();
		float targetRadius = target->GetRadius();

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

	inline MV1_COLL_RESULT_POLY_DIM CheckObstacleForward(const std::variant<CharacterBase*, Rooter*>& thisCharacter, bool isRight)
	{
		VECTOR pos = MyMath::VecZero();
		float radius = 0.0f;
		float rotY = 0.0f;

		std::visit([&](auto* character)
			{
				if (character != nullptr)
				{
					pos = character->GetPos();
					radius = character->GetRadius();
					rotY = character->GetRot().y;
				}
			}, thisCharacter);

		// 自身の中心
		VECTOR thisCenter = MyMath::VecAdd(pos, MyMath::VecY(radius));

		VECTOR forward = VGet(sinf(rotY), 0.0f, cosf(rotY));
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
}