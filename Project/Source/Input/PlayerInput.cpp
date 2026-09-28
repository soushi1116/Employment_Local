#include "PlayerInput.h"
#include "Input.h"

PlayerInput::PlayerInput() : InputBase()
{

}

PlayerInput::~PlayerInput()
{

}

int PlayerInput::GetInputBattle(BattleInput input)
{
	int result = 0;

	switch (input)
	{
	case BATTLE_INPUT_NONE:
		break;
	case INPUT_MOVE_X:
		result = Input::GetLeftStickX();
		break;
	case INPUT_MOVE_Y:
		result = Input::GetLeftStickY();
		break;
	case INPUT_ANGLE_ROT_X:
		result = Input::GetRightStickX();
		break;
	case INPUT_ANGLE_ROT_Y:
		result = Input::GetRightStickY();
		break;
	default:
		break;
	}

	return result;
}

bool PlayerInput::IsTriggerBattle(BattleTrigger trigger)
{
	bool result = false;

	switch (trigger)
	{
	case BATTLE_TRIGGER_NONE:
		break;
	case TRIGGER_ATTACK:
		result = Input::IsTriggerButton(Input::BUTTON_RB);
		break;
	case TRIGGER_SKILL:
		result = Input::IsTriggerButton(Input::BUTTON_B);
		break;
	case TRIGGER_SUPER_ATTACK:
		result = Input::IsTriggerButton(Input::BUTTON_LB);
		break;
	default:
		break;
	}

	return result;
}

bool PlayerInput::IsInputOther(OtherInput input)
{
	bool result = false;

	switch (input)
	{
	case OTHER_INPUT_NONE:
		break;
	case INPUT_CURSOR_UP:
		result = Input::IsLeftStickInput(Input::STICK_L_UP);
		break;
	case INPUT_CURSOR_DOWN:
		result = Input::IsLeftStickInput(Input::STICK_L_DOWN);
		break;
	case INPUT_CURSOR_RIGHT:
		result = Input::IsLeftStickInput(Input::STICK_L_RIGHT);
		break;
	case INPUT_CURSOR_LEFT:
		result = Input::IsLeftStickInput(Input::STICK_L_LEFT);
		break;
	default:
		break;
	}

	return result;
}

bool PlayerInput::IsTriggerOther(OtherTrigger trigger)
{
	bool result = false;

	switch (trigger)
	{
	case OTHER_TRIGGER_NONE:
		break;
	case INPUT_SELECT:
		result = Input::IsInputButton(Input::BUTTON_B);
		break;
	case INPUT_CANCEL:
		result = Input::IsInputButton(Input::BUTTON_A);
		break;
	default:
		break;
	}

	return result;
}