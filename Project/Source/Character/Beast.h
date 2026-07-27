#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

class Beast : public CharacterBase
{
public:
	Beast();
	~Beast();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;

	void Attack() override;
	void Skill() override;
	void SuperAttack() override;
};

