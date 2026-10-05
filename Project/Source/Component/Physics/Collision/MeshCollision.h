#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class MeshCollision : public CollisionBase
{
public:
	MeshCollision();
	~MeshCollision();

	void Draw() override;

	void SetCollisionHandle(const char* filePath);

	int GetCollisionHandle() { return m_CollisionHandle; }

public:

private:
	int m_CollisionHandle;
};

