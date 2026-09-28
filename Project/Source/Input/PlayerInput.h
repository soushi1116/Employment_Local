#pragma once
#include "InputBase.h"

class PlayerInput : public InputBase
{
public:
	PlayerInput();
	~PlayerInput();

	int GetInputBattle(BattleInput input);
	bool IsTriggerBattle(BattleTrigger trigger);
	bool IsInputOther(OtherInput input);
	bool IsTriggerOther(OtherTrigger trigger);

private:

};

