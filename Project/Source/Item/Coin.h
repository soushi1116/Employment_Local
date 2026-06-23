#pragma once
#include "DxLib.h"
#include "ItemBase.h"

class CollisionAABB;
struct HitResultAABB;

class Coin : public ItemBase
{
public:
	Coin();
	~Coin();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};

