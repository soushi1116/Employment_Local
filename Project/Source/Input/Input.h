#pragma once

namespace Input
{
	enum InputKey : unsigned int
	{
		KEY_NONE = 0,
		KEY_UP = (1U << 0),
		KEY_DOWN = (1U << 1),
		KEY_LEFT = (1U << 2),
		KEY_RIGHT = (1U << 3),
		KEY_W = (1U << 4),
		KEY_A = (1U << 5),
		KEY_S = (1U << 6),
		KEY_D = (1U << 7),
		KEY_Z = (1U << 8),
		KEY_X = (1U << 9),
		KEY_C = (1U << 10),
		KEY_Q = (1U << 11),
	};

	enum InputButton : unsigned int
	{
		BUTTON_NONE = 0,
		BUTTON_B = (1U << 0),
		BUTTON_A = (1U << 1),
		BUTTON_Y = (1U << 2),
		BUTTON_X = (1U << 3),
		BUTTON_RB = (1U << 4),
		BUTTON_LB = (1U << 5),
	};

	enum InputLeftStick : unsigned int
	{
		STICK_L_NONE = 0,
		STICK_L_UP = (1U << 0), 
		STICK_L_RIGHT = (1U << 1),
		STICK_L_DOWN = (1U << 2),
		STICK_L_LEFT = (1U << 3),
	};

	enum InputRightStick : unsigned int
	{
		STICK_R_NONE = 0,
		STICK_R_UP = (1U << 0),
		STICK_R_DOWN = (1U << 1),
		STICK_R_RIGHT = (1U << 2),
		STICK_R_LEFT = (1U << 3),
	};

	void Init();
	void Update();
	void Draw();
	void Fin();

	bool IsInputKey(InputKey key);
	bool IsTriggerKey(InputKey key);
	bool IsReleaseKey(InputKey key);
	bool IsHoldKey(InputKey key);

	bool IsInputButton(InputButton button);
	bool IsTriggerButton(InputButton button);
	bool IsReleaseButton(InputButton button);
	bool IsHoldButton(InputButton button);

	/*bool IsInputLeftStick(InputLeftStick left);
	bool IsTriggerLeftStick(InputLeftStick left);
	bool IsReleaseLeftStick(InputLeftStick left);
	bool IsHoldLeftStick(InputLeftStick left);*/

	int GetLeftStickX();
	int GetLeftStickY();

	int GetRightStickX();
	int GetRightStickY();

	bool IsLeftStickInput(InputLeftStick input);
}