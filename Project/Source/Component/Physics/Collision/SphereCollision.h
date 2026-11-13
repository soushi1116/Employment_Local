#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "CollisionBase.h"

class SphereCollision : public CollisionBase
{
public:
	SphereCollision(GameObject* owner);
	~SphereCollision();

	void Draw() override;

	float GetRadius() const { return m_Radius; }

private:
	float m_Radius;

};

