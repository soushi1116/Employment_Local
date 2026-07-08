#pragma once
#include "DxLib.h"
#include "BulletBase.h"

class CollisionAABB;
struct HitResultAABB;

class BotBeam : public BulletBase
{
public:
	BotBeam();
	~BotBeam();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};

