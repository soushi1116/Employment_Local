#include "DxLib.h"
#include "DamageCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../../MyColor/MyColor.h"
#include "../../GameObject.h"
#include <algorithm>

DamageCollision::DamageCollision()
{
	m_Radius = 0.0f;
	m_Active = false;
}

DamageCollision::~DamageCollision()
{

}

void DamageCollision::Draw()
{
	if (!m_Active) return;

	VECTOR collPos = m_Pos;

	collPos = VAdd(collPos, m_PosOffset);

	DrawSphere3D(collPos, m_Radius, 16, COLOR_WHITE, COLOR_WHITE, false);
}