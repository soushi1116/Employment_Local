#include "DxLib.h"
#include "Input.h"

int g_InputState;
int g_PrevInputState;

int g_ButtonState;
int g_PrevButtonState;

int g_LeftStickX;
int g_LeftStickY;

int g_RightStickX;
int g_RightStickY;

namespace Input
{
	void Init()
	{
		g_InputState = 0;
		g_PrevInputState = 0;

		g_ButtonState = 0;
		g_PrevButtonState = 0;

		g_LeftStickX = 0;
		g_LeftStickY = 0;
	}

	void Update()
	{
		g_PrevInputState = g_InputState;
		g_InputState = 0;

		g_PrevButtonState = g_ButtonState;
		g_ButtonState = 0;

		if (CheckHitKey(KEY_INPUT_UP))
		{
			g_InputState |= KEY_UP;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			g_InputState |= KEY_DOWN;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			g_InputState |= KEY_LEFT;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			g_InputState |= KEY_RIGHT;
		}
		if (CheckHitKey(KEY_INPUT_W))
		{
			g_InputState |= KEY_W;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			g_InputState |= KEY_A;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			g_InputState |= KEY_S;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			g_InputState |= KEY_D;
		}
		if (CheckHitKey(KEY_INPUT_Z))
		{
			g_InputState |= KEY_Z;
		}
		if (CheckHitKey(KEY_INPUT_X))
		{
			g_InputState |= KEY_X;
		}
		if (CheckHitKey(KEY_INPUT_C))
		{
			g_InputState |= KEY_C;
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			g_InputState |= KEY_Q;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B)
		{
			g_ButtonState |= BUTTON_B;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A)
		{
			g_ButtonState |= BUTTON_A;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_X)
		{
			g_ButtonState |= BUTTON_Y;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_C)
		{
			g_ButtonState |= BUTTON_X;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & (1 << 9))
		{
			g_ButtonState |= BUTTON_RB;
		}
		if (GetJoypadInputState(DX_INPUT_PAD1) & (1 << 8))
		{
			g_ButtonState |= BUTTON_LB;
		}
	}

	void Draw()
	{
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d" , GetJoypadInputState(DX_INPUT_PAD1), TRUE);
	}

	void Fin()
	{

	}

	//KeyBord
	bool IsInputKey(InputKey key)
	{
		return g_InputState & key;
	}

	bool IsTriggerKey(InputKey key)
	{
		return (g_InputState & key) && !(g_PrevInputState & key);
	}

	bool IsReleaseKey(InputKey key)
	{
		return !(g_InputState & key) && (g_PrevInputState & key);
	}

	bool IsHoldKey(InputKey key)
	{
		return (g_InputState & key) && (g_PrevInputState & key);
	}

	// Button
	bool IsInputButton(InputButton key)
	{
		return g_ButtonState & key;
	}

	bool IsTriggerButton(InputButton key)
	{
		return (g_ButtonState & key) && !(g_PrevButtonState & key);
	}

	bool IsReleaseButton(InputButton key)
	{
		return !(g_ButtonState & key) && (g_PrevButtonState & key);
	}

	bool IsHoldButton(InputButton key)
	{
		return (g_ButtonState & key) && (g_PrevButtonState & key);
	}

	// LeftStick
	int GetLeftStickX()
	{
		GetJoypadAnalogInput(&g_LeftStickX, &g_LeftStickY, DX_INPUT_PAD1);

		return g_LeftStickX;
	}

	int GetLeftStickY()
	{
		GetJoypadAnalogInput(&g_LeftStickX, &g_LeftStickY, DX_INPUT_PAD1);

		return g_LeftStickY;
	}

	// RightStick
	int GetRightStickX()
	{
		GetJoypadAnalogInputRight(&g_RightStickX, &g_RightStickY, DX_INPUT_PAD1);

		return g_RightStickX;
	}

	int GetRightStickY()
	{
		GetJoypadAnalogInputRight(&g_RightStickX, &g_RightStickY, DX_INPUT_PAD1);

		return g_RightStickY;
	}
}