#pragma once
#include "DxLib.h"
#include "BulletBase.h"

class CollisionAABB;
struct HitResultAABB;

class BeastJumpWave : public BulletBase
{
public:
	BeastJumpWave();
	~BeastJumpWave();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};

