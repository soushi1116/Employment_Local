#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

class Boss : public CharacterBase
{
public:
	Boss();
	~Boss();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	void Attack() override;
	void Skill() override;
	void SuperAttack() override;
};

