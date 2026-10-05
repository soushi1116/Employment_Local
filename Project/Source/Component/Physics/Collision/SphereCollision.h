#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class SphereCollision : public CollisionBase
{
public:
	SphereCollision();
	~SphereCollision();

	void Draw() override;

	float GetRadius() { return m_Radius; }

private:
	float m_Radius;

};

