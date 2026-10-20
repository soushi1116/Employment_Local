#include "DxLib.h"
#include "BoxCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../GameObject.h"

BoxCollision::BoxCollision(GameObject* owner) : CollisionBase(owner)
{
}

BoxCollision::~BoxCollision()
{

}

void BoxCollision::Draw()
{
	m_Size = MyMath::VecScale(m_Size, 10000.0f);

	VECTOR posA, posB;

	posA = VGet(GetLeft(), GetBottom(), GetBack());
	posB = VGet(GetRight(), GetTop(), GetFront());

	DrawCube3D(posA, posB, GetColor(255, 255, 255), GetColor(255, 255, 255), true);
}

void BoxCollision::MultSize(VECTOR mult)
{
	m_Size = MyMath::VecScaleVector(m_Size, mult);
}

//HitResultAABB BoxCollision::CheckAABB(const BoxCollision* other) const
//{
//	HitResultAABB result = {};
//
//	if (other == nullptr)
//	{
//		return result;
//	}
//
//	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
//	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
//	VECTOR otherSize = other->GetSize();
//
//	float left = centerPos.x - m_Size.x * 0.5f;
//	float right = centerPos.x + m_Size.x * 0.5f;
//	float top = centerPos.y + m_Size.y * 0.5f;
//	float bottom = centerPos.y - m_Size.y * 0.5f;
//	float front = centerPos.z - m_Size.z * 0.5f;
//	float back = centerPos.z + m_Size.z * 0.5f;
//
//	float otherLeft = otherCenterPos.x - otherSize.x * 0.5f;
//	float otherRight = otherCenterPos.x + otherSize.x * 0.5f;
//	float otherTop = otherCenterPos.y + otherSize.y * 0.5f;
//	float otherBottom = otherCenterPos.y - otherSize.y * 0.5f;
//	float otherFront = otherCenterPos.z - otherSize.z * 0.5f;
//	float otherBack = otherCenterPos.z + otherSize.z * 0.5f;
//
//	if ((left < otherRight && right > otherLeft)
//		&& (bottom < otherTop && top > otherBottom)
//		&& (front < otherBack && back > otherFront))
//	{
//		result.m_IsHit = true;
//		result.m_HitPos = otherCenterPos;
//		result.m_HitSize = otherSize;
//		result.m_HitLeft = otherLeft;
//		result.m_HitRight = otherRight;
//		result.m_HitTop = otherTop;
//		result.m_HitBottom = otherBottom;
//		result.m_HitFront = otherFront;
//		result.m_HitBack = otherBack;
//	}
//
//	return result;
//}