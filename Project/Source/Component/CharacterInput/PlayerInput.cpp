#include "PlayerInput.h"
#include "../../Input/Input.h"

PlayerInput::PlayerInput(GameObject* owner) : InputBase(owner)
{
	m_Type = INPUT_TYPE_PLAYER;
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::CheckInput()
{
	m_BattleInputData.m_LeftStickX = Input::GetLeftStickX();
	m_BattleInputData.m_LeftStickY = Input::GetLeftStickY();
	m_BattleInputData.m_RightStickX = Input::GetRightStickX();
	m_BattleInputData.m_RightStickY = Input::GetRightStickY();

	if (Input::IsTriggerButton(Input::BUTTON_RB))
	{
		m_BattleTrigger = TRIGGER_ATTACK;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		m_BattleTrigger = TRIGGER_SKILL;
	}

	if (Input::IsTriggerButton(Input::BUTTON_LB))
	{
		m_BattleTrigger = TRIGGER_SUPER_ATTACK;
	}
}