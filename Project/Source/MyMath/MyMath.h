#pragma once

#include "DxLib.h"

namespace MyMath
{
	VECTOR VecCreate(VECTOR startPos, VECTOR endPos);
	VECTOR VecAdd(VECTOR vecA, VECTOR vecB);
	VECTOR VecScale(VECTOR vec, float scale);
	VECTOR VecScaleVector(VECTOR vecA, VECTOR vecB);
	float VecLong(VECTOR vec);
	VECTOR VecNormarize(VECTOR vec);
	VECTOR VecForwardZX(float rotY);
	
	VECTOR VecZero();
	VECTOR Vec2D(float x, float y);

	VECTOR VecX(float x);
	VECTOR VecY(float y);
	VECTOR VecZ(float z);
	VECTOR VecSame(float f);

	bool IsVecZero(VECTOR vec);

	struct VECTOR_INT
	{
		int x; int y; int z;
	};

	struct VECTOR_2D
	{
		float x; float y;
	};

	VECTOR_INT VGetInt(int x, int y, int z);
	VECTOR_INT Vec2DInt(int x, int y);

	MATRIX MatCreate();
	MATRIX MatMult(MATRIX matA, MATRIX matB);
	MATRIX MatTranslation(VECTOR trans);
	MATRIX MatRotationPitch(float pitch);
	MATRIX MatRotationYaw(float yaw);
	MATRIX MatRotationRoll(float roll);
	VECTOR MatTransform(MATRIX transMat, VECTOR pos);
}