#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class SphereCollision : public CollisionBase
{
public:
	SphereCollision(GameObject* owner);
	~SphereCollision();

	void Draw() override;

public:
	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetRadius(float radius) { m_Radius = radius; }

	VECTOR GetTargetPos() { return *m_TargetPos; }
	VECTOR GetLocalPos() { return m_LocalPos; }
	VECTOR GetWorldPos();
	float GetRadius() { return m_Radius; }

private:
	VECTOR* m_TargetPos;
	VECTOR m_LocalPos;
	float m_Radius;

	VECTOR m_Pos;
};

