#include "DxLib.h"
#include "CharacterInput.h"
#include "InputBase.h"
#include "PlayerInput.h"

CharacterInput::CharacterInput(GameObject* owner) : Component(owner)
{
	m_CompName = "Input";
}

CharacterInput::~CharacterInput()
{
	
}

void CharacterInput::Step()
{
	m_Input->ResetInput();

	if (m_Input->GetInputType() == INPUT_TYPE_PLAYER)
	{
		auto playerInput = std::dynamic_pointer_cast<PlayerInput>(m_Input);

		playerInput->CheckInput();
	}
}

void CharacterInput::InputLeftStickX(int input) 
{ 
	if (m_Input) m_Input->InputLeftStickX(input); 
}

void CharacterInput::InputLeftStickY(int input)
{
	if (m_Input) m_Input->InputLeftStickY(input);
}

void CharacterInput::InputRightStickX(int input)
{
	if (m_Input) m_Input->InputRightStickX(input);
}

void CharacterInput::InputRightStickY(int input) 
{
	if (m_Input) m_Input->InputRightStickY(input);
}

void CharacterInput::TriggerButton(BattleTrigger trigger) 
{ 
	if (m_Input) m_Input->TriggerButton(trigger);
}

int CharacterInput::GetInputBattle(BattleInput input) 
{ 
	return m_Input ? m_Input->GetInputBattle(input) : 0;
}

bool CharacterInput::IsTriggerBattle(BattleTrigger trigger) 
{ 
	return m_Input ? m_Input->IsTriggerBattle(trigger) : false;
}