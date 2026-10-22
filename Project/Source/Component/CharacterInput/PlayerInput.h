#pragma once
#include "InputBase.h"

class InputBase;

class PlayerInput : public InputBase
{
public:
	PlayerInput(GameObject* owner);
	~PlayerInput();

	void CheckInput();

private:

};

