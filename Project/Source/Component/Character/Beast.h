#pragma once
#include "DxLib.h"
#include "CharacterMove.h"

class GameObject;

class Beast : public CharacterMove
{
public:
	Beast(GameObject* owner);
	~Beast();

public:
	void Update() override;

public:
	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

private:
	float m_SuperAttackModelPosOffset;
};