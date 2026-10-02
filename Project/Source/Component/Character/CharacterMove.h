#pragma once
#include "DxLib.h"
#include "../Component.h"

class CharacterMove : public Component
{
public:
	CharacterMove(GameObject* owner);
	~CharacterMove();

	void Step();
	void Update();

private:
	VECTOR m_Move;
	float m_Gravity;
};