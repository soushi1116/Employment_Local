#pragma once
#include "DxLib.h"
#include "../Component.h"
#include "../../Input/InputParameter.h"

class GameObject;

class InputBase : public Component
{
public:
	InputBase(GameObject* owner);
	~InputBase();

	void ResetInput()
	{
		m_BattleInput = BATTLE_INPUT_NONE;
		m_BattleTrigger = BATTLE_TRIGGER_NONE;
	}

	virtual void InputLeftStickX(int input);
	virtual void InputLeftStickY(int input);
	virtual void InputRightStickX(int input);
	virtual void InputRightStickY(int input);
	virtual void TriggerButton(BattleTrigger trigger);

	virtual int GetInputBattle(BattleInput input);
	virtual bool IsTriggerBattle(BattleTrigger trigger);

	InputType GetInputType() { return m_Type; }

protected:
	InputType m_Type;
	BattleInput m_BattleInput;
	BattleInputData m_BattleInputData;
	BattleTrigger m_BattleTrigger;
	GameObject* m_Owner;
};