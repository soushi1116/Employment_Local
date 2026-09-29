#include "InputBase.h"
#include "Input.h"

InputBase::InputBase()
{
	m_Type = INPUT_TYPE_NONE;
	m_BattleInput = BATTLE_INPUT_NONE;
	m_BattleInputData = { 0 };
	m_BattleTrigger = BATTLE_TRIGGER_NONE;
	m_OtherInput = OTHER_INPUT_NONE;
	m_OtherTrigger = OTHER_TRIGGER_NONE;
}

InputBase::~InputBase()
{
	
}

void InputBase::InputLeftStickX(int input)
{
	m_BattleInputData.m_LeftStickX = input;
}

void InputBase::InputLeftStickY(int input)
{
	m_BattleInputData.m_LeftStickY = input;
}

void InputBase::InputRightStickX(int input)
{
	m_BattleInputData.m_RightStickX = input;
}

void InputBase::InputRightStickY(int input)
{
	m_BattleInputData.m_RightStickY = input;
}

void InputBase::TriggerButton(BattleTrigger trigger)
{
	if (m_BattleTrigger == BATTLE_TRIGGER_NONE || trigger == BATTLE_TRIGGER_NONE)
	{
		m_BattleTrigger = trigger;
	}
}

int InputBase::GetInputBattle(BattleInput input)
{
	int result = 0;

	switch (input)
	{
	case BATTLE_INPUT_NONE:
		break;
	case INPUT_MOVE_X:
		result = m_BattleInputData.m_LeftStickX;
		break;
	case INPUT_MOVE_Y:
		result = m_BattleInputData.m_LeftStickY;
		break;
	case INPUT_ANGLE_ROT_X:
		result = m_BattleInputData.m_RightStickX;
		break;
	case INPUT_ANGLE_ROT_Y:
		result = m_BattleInputData.m_RightStickY;
		break;
	default:
		break;
	}

	return result;
}

bool InputBase::IsTriggerBattle(BattleTrigger trigger)
{
	return (m_BattleTrigger & trigger) != 0;
}

bool InputBase::IsInputOther(OtherInput input)
{
	bool result = false;

	switch (input)
	{
	case OTHER_INPUT_NONE:
		break;
	case INPUT_CURSOR_UP:
		result = Input::IsLeftStickInput(Input::STICK_L_UP);
		break;
	case INPUT_CURSOR_DOWN:
		result = Input::IsLeftStickInput(Input::STICK_L_DOWN);
		break;
	case INPUT_CURSOR_RIGHT:
		result = Input::IsLeftStickInput(Input::STICK_L_RIGHT);
		break;
	case INPUT_CURSOR_LEFT:
		result = Input::IsLeftStickInput(Input::STICK_L_LEFT);
		break;
	default:
		break;
	}

	return result;
}

bool InputBase::IsTriggerOther(OtherTrigger trigger)
{
	bool result = false;

	switch (trigger)
	{
	case OTHER_TRIGGER_NONE:
		break;
	case INPUT_SELECT:
		result = Input::IsInputButton(Input::BUTTON_B);
		break;
	case INPUT_CANCEL:
		result = Input::IsInputButton(Input::BUTTON_A);
		break;
	default:
		break;
	}

	return result;
}