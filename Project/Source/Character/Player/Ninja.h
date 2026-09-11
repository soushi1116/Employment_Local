#pragma once
#include "DxLib.h"
#include "../CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

class Ninja : public CharacterBase
{
public:
	Ninja();
	~Ninja();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;

	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

	virtual CharacterBase* Clone() const override
	{
		return new Ninja(*this);
	}

private:
	int m_InvisibleStartTime;
};

