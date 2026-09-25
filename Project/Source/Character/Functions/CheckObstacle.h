#pragma once

#include "DxLib.h"
#include "../../MyMath/MyMath.h"
#include "../CharacterBase.h"
#include "../Rooter/Rooter.h"
#include "../../Map/MapManager.h"
#include "../../MyColor/MyColor.h"

namespace CheckObstacle
{
	struct ForwardResult
	{
		bool isHit;
		VECTOR normal;
	};

	MV1_COLL_RESULT_POLY CheckObstacleTargetCharacter(CharacterBase* thisCharacter, CharacterBase* target);

	MV1_COLL_RESULT_POLY CheckObstacleTargetRooter(Rooter* thisRooter, CharacterBase* target);

	MV1_COLL_RESULT_POLY CheckObstacleTarget(VECTOR thisPos, float thisRadius, VECTOR targetPos, float targetRadius);


	MV1_COLL_RESULT_POLY_DIM CheckObstacleForwardCharacter(CharacterBase* thisCharacter, bool isRight);

	MV1_COLL_RESULT_POLY_DIM CheckObstacleForwardRooter(Rooter* thisRooter, bool isRight);

	MV1_COLL_RESULT_POLY_DIM CheckObstacleForward(VECTOR pos, VECTOR rot, float radius, bool isRight);

	ForwardResult GetForwardResult(MV1_COLL_RESULT_POLY_DIM coll);
}