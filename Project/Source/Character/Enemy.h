#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	void Damage();

private:

};

