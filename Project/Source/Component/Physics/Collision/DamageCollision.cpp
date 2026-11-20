#include "DxLib.h"
#include "DamageCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../../MyColor/MyColor.h"
#include "../../GameObject.h"
#include <algorithm>

DamageCollision::DamageCollision(GameObject* owner)
	: CollisionBase(owner)
	, m_Radius(0.0f)
	, m_Active(false)
	, m_IsBoss(false)
	, m_Damage(0)
	, m_ParentIndex(0)
{

}

DamageCollision::~DamageCollision()
{

}

void DamageCollision::Draw()
{
	if (!m_Active) return;

#ifdef _DEBUG
	VECTOR collPos = m_Pos;

	collPos = VAdd(collPos, m_PosOffset);

	DrawSphere3D(collPos, m_Radius, 16, COLOR_RED, COLOR_RED, false);
#endif

}