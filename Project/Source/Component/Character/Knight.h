#pragma once
#include "DxLib.h"
#include "CharacterMove.h"

class GameObject;

class Knight : public CharacterMove
{
public:
	Knight(GameObject* owner);
	~Knight();

public:
	void Update() override;

public:
	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

private:

};