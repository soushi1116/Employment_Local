#pragma once
#include "DxLib.h"
#include "CharacterMove.h"

class GameObject;

class Robot : public CharacterMove
{
public:
	Robot(GameObject* owner);
	~Robot();

public:
	void Update() override;

public:
	void Attack() override;
	void Skill() override;
	void SuperAttack() override;

private:
	bool m_ThrowFlg;
};