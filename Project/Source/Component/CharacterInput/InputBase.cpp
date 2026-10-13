#include "InputBase.h"
#include "../../Input/Input.h"

InputBase::InputBase(GameObject* owner) : Component(owner)
{
	m_Type = INPUT_TYPE_NONE;
	m_BattleInput = BATTLE_INPUT_NONE;
	m_BattleInputData = { 0 };
	m_BattleTrigger = BATTLE_TRIGGER_NONE;
	m_Owner = owner;
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
