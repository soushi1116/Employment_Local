#pragma once

#include "DxLib.h"

class CollisionSphere
{
public:
	CollisionSphere();
	~CollisionSphere();

public:
	void Draw();

public:
	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetRadius(float radius) { m_Radius = radius; }

	VECTOR GetTargetPos() { return *m_TargetPos; }
	VECTOR GetLocalPos() { return m_LocalPos; }
	VECTOR GetWorldPos();
	float GetRadius() { return m_Radius; }

public:
	bool CheckSphere(CollisionSphere* other);

private:
	VECTOR* m_TargetPos;
	VECTOR m_LocalPos;
	float m_Radius;
};