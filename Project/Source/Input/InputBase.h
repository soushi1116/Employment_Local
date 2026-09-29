#pragma once
#include "DxLib.h"
#include "InputParameter.h"

class InputBase
{
public:
	InputBase();
	~InputBase();

	virtual void InputLeftStickX(int input);
	virtual void InputLeftStickY(int input);
	virtual void InputRightStickX(int input);
	virtual void InputRightStickY(int input);
	virtual void TriggerButton(BattleTrigger trigger);

	virtual int GetInputBattle(BattleInput input);
	virtual bool IsTriggerBattle(BattleTrigger trigger);
	virtual bool IsInputOther(OtherInput input);
	virtual bool IsTriggerOther(OtherTrigger trigger);

protected:
	InputType m_Type;
	BattleInput m_BattleInput;
	BattleInputData m_BattleInputData;
	BattleTrigger m_BattleTrigger;
	OtherInput m_OtherInput;
	OtherTrigger m_OtherTrigger;
};