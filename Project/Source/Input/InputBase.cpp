#include "InputBase.h"
#include "../Character/CharacterManager.h"

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

