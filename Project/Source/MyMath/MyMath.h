#pragma once

#include "DxLib.h"

namespace MyMath
{
	VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	VECTOR VecScale(VECTOR vecA, float scale);
	float VecLong(VECTOR vec);
	VECTOR VecNormarize(VECTOR vec);
	VECTOR VecForwardZX(float rotY);

	MATRIX MatCreate();
	MATRIX MatMult(MATRIX matA, MATRIX matB);
	MATRIX MatTranslation(VECTOR trans);
	MATRIX MatRotationPitch(float pitch);
	MATRIX MatRotationYaw(float yaw);
	MATRIX MatRotationRoll(float roll);
	VECTOR MatTransform(MATRIX transMat, VECTOR pos);
}