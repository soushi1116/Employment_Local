#pragma once
#include "DxLib.h"
#include "BulletBase.h"

class CollisionAABB;
struct HitResultAABB;

class PoisonLeaf : public BulletBase
{
public:
	PoisonLeaf();
	~PoisonLeaf();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};

