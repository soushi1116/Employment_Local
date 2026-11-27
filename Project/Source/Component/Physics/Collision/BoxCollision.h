#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "CollisionBase.h"

class BoxCollision : public CollisionBase
{
public:
	BoxCollision(GameObject* owner);
	~BoxCollision();

	void Draw() override;

};
