#include "DxLib.h"
#include "BoxCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../../MyColor/MyColor.h"
#include "../../GameObject.h"
#include <algorithm>

BoxCollision::BoxCollision(GameObject* owner)
	: CollisionBase(owner)
{

}

BoxCollision::~BoxCollision()
{

}

void BoxCollision::Draw()
{
	VECTOR minPos = VAdd(m_Pos, VScale(m_Size, -0.5f));
	VECTOR maxPos = VAdd(m_Pos, VScale(m_Size, 0.5f));

#ifdef _DEBUG
	DrawCube3D(minPos, maxPos, COLOR_WHITE, COLOR_WHITE, false);
#endif

}