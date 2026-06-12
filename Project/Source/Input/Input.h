#pragma once

namespace Input
{
	enum InputKey
	{
		KEY_UP = (1 << 0),
		KEY_DOWN = (1 << 1),
		KEY_LEFT = (1 << 2),
		KEY_RIGHT = (1 << 3),
		KEY_W = (1 << 4),
		KEY_A = (1 << 5),
		KEY_S = (1 << 6),
		KEY_D = (1 << 7),
		KEY_Z = (1 << 8),
		KEY_X = (1 << 9),
		KEY_C = (1 << 10),
		KEY_Q = (1 << 11),
	};

	enum InputButton
	{
		BUTTON_B = (1 << 12),
		BUTTON_X = (1 << 13),
		BUTTON_RB = (1 << 14),
		BUTTON_LB = (1 << 15),
	};

	enum InputLeftStick
	{
		STICK_L_UP = (1 << 16), 
		STICK_L_RIGHT = (1 << 17),
		STICK_L_DOWN = (1 << 18),
		STICK_L_LEFT = (1 << 19),
	};

	enum InputRighttStick
	{
		STICK_R_UP = (1 << 20),
		STICK_R_RIGHT = (1 << 21),
		STICK_R_DOWN = (1 << 22),
		STICK_R_LEFT = (1 << 23),
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
}