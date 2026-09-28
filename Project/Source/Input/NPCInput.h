#pragma once
#include "InputBase.h"

class NPCInput : public InputBase
{
public:
	NPCInput();
	~NPCInput();

	int GetInputBattle(BattleInput input);
	bool IsTriggerBattle(BattleTrigger trigger);
	bool IsInputOther(OtherInput input);
	bool IsTriggerOther(OtherTrigger trigger);

public:
	void InputLeftStickX(int input);
	void InputLeftStickY(int input);
	void InputRightStickX(int input);
	void InputRightStickY(int input);
	void TriggerButton(BattleTrigger trigger);

private:

};
