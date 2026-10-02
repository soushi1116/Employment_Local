#pragma once

#include "DxLib.h"
#include "../../MyMath/MyMath.h"
#include "../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class MeshCollision : public CollisionBase
{
public:
	MeshCollision(GameObject* owner);
	~MeshCollision();

	void Draw() override;

	void SetCollisionHandle(const char* filePath);

public:

private:
	VECTOR m_Pos;

	int m_CollisionHandle;
};

