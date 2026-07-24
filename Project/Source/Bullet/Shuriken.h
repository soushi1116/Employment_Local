#pragma once
#include "DxLib.h"
#include "BulletBase.h"

class CollisionAABB;
struct HitResultAABB;

class Shuriken : public BulletBase
{
public:
	Shuriken();
	~Shuriken();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};

