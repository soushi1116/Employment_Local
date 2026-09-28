#include "NPCInput.h"
#include "Input.h"

NPCInput::NPCInput() : InputBase()
{

}

NPCInput::~NPCInput()
{

}

int NPCInput::GetInputBattle(BattleInput input)
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

bool NPCInput::IsTriggerBattle(BattleTrigger trigger)
{
	return m_BattleTrigger && trigger;
}

bool NPCInput::IsInputOther(OtherInput input)
{
	return false;
}

bool NPCInput::IsTriggerOther(OtherTrigger trigger)
{
	return false;
}

void NPCInput::InputLeftStickX(int input)
{
	m_BattleInputData.m_LeftStickX = input;
}

void NPCInput::InputLeftStickY(int input)
{
	m_BattleInputData.m_LeftStickY = input;
}

void NPCInput::InputRightStickX(int input)
{
	m_BattleInputData.m_RightStickX = input;
}

void NPCInput::InputRightStickY(int input)
{
	m_BattleInputData.m_RightStickY = input;
}

void NPCInput::TriggerButton(BattleTrigger trigger)
{
	m_BattleTrigger = trigger;
}