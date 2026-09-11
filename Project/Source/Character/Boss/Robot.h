#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

class Robot : public CharacterBase
{
public:
	Robot();
	~Robot();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

	virtual CharacterBase* Clone() const override
	{
		return new Robot(*this);
	}
};

