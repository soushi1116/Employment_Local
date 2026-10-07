#pragma once
#include "DxLib.h"
#include "../Component.h"

class _3DPhysics;
class CharacterInput;
class CharacterParameter;
class Animator;

class CharacterMove : public Component
{
public:
	CharacterMove(GameObject* owner);
	~CharacterMove();

	void Start() override;
	void Step() override;
	void Update() override;

private:
	std::shared_ptr<_3DPhysics> m_3DPhysics;
	std::shared_ptr<CharacterInput> m_Input;
	std::shared_ptr<CharacterParameter> m_Parameter;
	std::shared_ptr<Animator> m_Animator;
};