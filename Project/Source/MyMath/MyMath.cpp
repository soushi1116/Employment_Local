#include "MyMath.h"
#include <math.h>

namespace MyMath
{
	VECTOR VecCreate(VECTOR startPos, VECTOR endPos)
	{
		VECTOR result = VGet(0.0f, 0.0f, 0.0f);

		result.x = endPos.x - startPos.x;
		result.y = endPos.y - startPos.y;
		result.z = endPos.z - startPos.z;

		return result;
	}

	VECTOR VecAdd(VECTOR vecA, VECTOR vecB)
	{
		VECTOR result = VGet(0.0f, 0.0f, 0.0f);

		result.x = vecA.x + vecB.x;
		result.y = vecA.y + vecB.y;
		result.z = vecA.z + vecB.z;

		return result;
	}

	VECTOR VecScale(VECTOR vecA, float scale)
	{

		VECTOR result = VGet(0.0f, 0.0f, 0.0f);

		result.x = vecA.x * scale;
		result.y = vecA.y * scale;
		result.z = vecA.z * scale;

		return result;
	}

	float VecLong(VECTOR vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	VECTOR VecNormarize(VECTOR vec)
	{
		float vecLong = VecLong(vec);

		if (vecLong == 0.0f) return VGet(0.0f, 0.0f, 0.0f);

		return VecScale(vec, 1.0f / vecLong);
	}

	VECTOR VecForwardZX(float rotY)
	{
		VECTOR result;

		result.x = sinf(rotY);
		result.y = 0.0f;
		result.z = cosf(rotY);

		return result;
	}

	MATRIX MatCreate()
	{
		MATRIX result = { 0 };

		for (int i = 0; i < 4; i++)
		{
			result.m[i][i] = 1.0f;
		}

		return result;
	}

	MATRIX MatMult(MATRIX matA, MATRIX matB)
	{
		MATRIX result = { 0 };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					result.m[i][j] += matA.m[i][k] * matB.m[k][j];
				}
			}
		}

		return result;
	}

	MATRIX MatTranslation(VECTOR trans)
	{
		MATRIX result = MatCreate();

		result.m[0][3] = trans.x;
		result.m[1][3] = trans.y;
		result.m[2][3] = trans.z;

		return result;
	}

	MATRIX MatRotationPitch(float pitch)
	{
		MATRIX result = MatCreate();

		result.m[1][1] = cosf(pitch);
		result.m[1][2] = -sinf(pitch);
		result.m[2][1] = sinf(pitch);
		result.m[2][2] = cosf(pitch);

		return result;
	}

	MATRIX MatRotationYaw(float yaw)
	{
		MATRIX result = MatCreate();

		result.m[0][0] = cosf(yaw);
		result.m[0][2] = sinf(yaw);
		result.m[2][0] = -sinf(yaw);
		result.m[2][2] = cosf(yaw);

		return result;
	}

	MATRIX MatRotationRoll(float roll)
	{
		MATRIX result = MatCreate();

		result.m[0][0] = cosf(roll);
		result.m[0][1] = -sinf(roll);
		result.m[1][0] = sinf(roll);
		result.m[1][1] = cosf(roll);

		return result;
	}

	VECTOR MatTransform(MATRIX transMat, VECTOR pos)
	{
		VECTOR result = { 0 };

		float posBuffer[4] = { pos.x, pos.y, pos.z, 1.0f };

		float resultBuffer[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				resultBuffer[i] += transMat.m[i][j] * posBuffer[j];
			}
		}

		result.x = resultBuffer[0];
		result.y = resultBuffer[1];
		result.z = resultBuffer[2];

		return result;
	}
}