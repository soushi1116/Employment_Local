#pragma once
#include "DxLib.h"
#include "InputParameter.h"

class CharacterBase;

class InputBase
{
public:
	InputBase();
	~InputBase();

	virtual int GetInputBattle(BattleInput input) = 0;
	virtual bool IsTriggerBattle(BattleTrigger trigger) = 0;
	virtual bool IsInputOther(OtherInput input) = 0;
	virtual bool IsTriggerOther(OtherTrigger trigger) = 0;

protected:
	InputType m_Type;
	BattleInput m_BattleInput;
	BattleInputData m_BattleInputData;
	BattleTrigger m_BattleTrigger;
	OtherInput m_OtherInput;
	OtherTrigger m_OtherTrigger;
};