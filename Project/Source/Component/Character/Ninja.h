#pragma once
#include "DxLib.h"
#include "CharacterMove.h"

class GameObject;

class Ninja : public CharacterMove
{
public:
	Ninja(GameObject* owner);
	~Ninja();

public:
	void Update() override;

public:
	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

private:

};