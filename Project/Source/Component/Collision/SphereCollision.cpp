#include "DxLib.h"
#include "SphereCollision.h"
#include "../../MyMath/MyMath.h"
#include "../../MyColor/MyColor.h"
#include "../GameObject.h"
#include <algorithm>

SphereCollision::SphereCollision(GameObject* owner) : CollisionBase(owner)
{
	m_TargetPos = nullptr;
	m_LocalPos = MyMath::VecZero();
	m_Radius = 0.0f;
	m_Pos = MyMath::VecZero();
}

SphereCollision::~SphereCollision()
{

}

void SphereCollision::Draw()
{
	m_Pos = m_Owner->GetComponent<Transform>()->GetPos();
	VECTOR size = m_Owner->GetComponent<Transform>()->GetScale();

	m_Pos = VAdd(m_Pos, m_PosOffset);

	m_Radius = (std::max)({ size.x, size.y, size.z });

	m_Radius *= 1.0f;

	DrawSphere3D(m_Pos, m_Radius, 16, COLOR_WHITE, COLOR_WHITE, false);
}