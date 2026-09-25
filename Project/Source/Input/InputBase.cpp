#include "InputBase.h"
#include "../Character/CharacterManager.h"

InputBase::InputBase()
{
	m_Type = INPUT_TYPE_NONE;
	m_BattleInput = BATTLE_INPUT_NONE;
	m_OtherInput = OTHER_INPUT_NONE;
	m_InBattleScene = false;
	m_ParentCharacter = nullptr;
}

InputBase::~InputBase()
{
	Fin();
}

void InputBase::Init()
{

}

void InputBase::Start()
{
	m_InBattleScene = m_ParentCharacter->InBattleScene();
}