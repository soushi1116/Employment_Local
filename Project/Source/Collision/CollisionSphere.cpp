#include "DxLib.h"
#include "CollisionSphere.h"
#include "../MyMath/MyMath.h"

CollisionSphere::CollisionSphere()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
}

CollisionSphere::~CollisionSphere()
{

}

void CollisionSphere::Draw()
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);

	DrawSphere3D(centerPos, m_Radius, 16, GetColor(255, 255, 255), GetColor(255, 255, 255), false);
}

VECTOR CollisionSphere::GetWorldPos()
{
	return MyMath::VecAdd(*m_TargetPos, m_LocalPos);
}

bool CollisionSphere::CheckSphere(CollisionSphere* other)
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	float otherRadius = other->GetRadius();

	VECTOR vec = MyMath::VecCreate(centerPos, otherCenterPos);
	float distance = MyMath::VecLong(vec);

#ifdef _DEBUG
	char buf[256];
	sprintf_s(buf, "MyPos:(%.1f, %.1f, %.1f) OtherPos:(%.1f, %.1f, %.1f) Dist:%.1f TotalRad:%.1f\n",
		centerPos.x, centerPos.y, centerPos.z,
		otherCenterPos.x, otherCenterPos.y, otherCenterPos.z,
		distance, (m_Radius + otherRadius));
	OutputDebugStringA(buf);
#endif

	if (distance <= m_Radius + otherRadius)
	{
		return true;
	}

	return false;
}