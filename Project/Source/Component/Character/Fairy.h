#pragma once
#include "DxLib.h"
#include "CharacterMove.h"

class GameObject;

class Fairy : public CharacterMove
{
public:
	Fairy(GameObject* owner);
	~Fairy();

public:
	void Update() override;

public:
	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

private:
	bool m_ThrowFlg;
};