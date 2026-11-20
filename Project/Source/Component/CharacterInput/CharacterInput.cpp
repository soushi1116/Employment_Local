#include "DxLib.h"
#include "CharacterInput.h"
#include "InputBase.h"
#include "PlayerInput.h"

CharacterInput::CharacterInput(GameObject* owner) : Component(owner)
{
	
}

CharacterInput::~CharacterInput()
{
	
}

void CharacterInput::Step()
{
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->ResetInput();

		if (inputPtr->GetInputType() == INPUT_TYPE_PLAYER)
		{
			auto playerInput = std::dynamic_pointer_cast<PlayerInput>(inputPtr);

			playerInput->CheckInput();
		}
	}
}

void CharacterInput::InputLeftStickX(int input) 
{ 
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->InputLeftStickX(input);
	}
}

void CharacterInput::InputLeftStickY(int input)
{
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->InputLeftStickY(input);
	}
}

void CharacterInput::InputRightStickX(int input)
{
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->InputRightStickX(input);
	}
}

void CharacterInput::InputRightStickY(int input) 
{
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->InputRightStickY(input);
	}
}

void CharacterInput::TriggerButton(BattleTrigger trigger) 
{
	if (auto inputPtr = m_Input.lock())
	{
		inputPtr->TriggerButton(trigger);
	}
}

int CharacterInput::GetInputBattle(BattleInput input) 
{
	if (auto inputPtr = m_Input.lock())
	{
		return inputPtr->GetInputBattle(input);
	}
	return 0;
}

bool CharacterInput::IsTriggerBattle(BattleTrigger trigger) 
{
	if (auto inputPtr = m_Input.lock())
	{
		return inputPtr->IsTriggerBattle(trigger);
	}
	return false;
}