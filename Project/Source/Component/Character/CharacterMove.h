#pragma once
#include "DxLib.h"
#include "../Component.h"

class _3DPhysics;
class CharacterInput;

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
};