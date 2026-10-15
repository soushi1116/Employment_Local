#pragma once
#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class DamageCollision : public CollisionBase
{
public:
	DamageCollision();
	~DamageCollision();

	void Draw() override;

	float GetRadius() const { return m_Radius; }
	bool IsActive() const { return m_Active; }

	void SetRadius(float radius) { m_Radius = radius; }
	void SetActive(bool active) { m_Active = active; }

private:
	float m_Radius;
	bool m_Active;
};