#include "DxLib.h"
#include "Input.h"

int g_InputState;
int g_PrevInputState;

namespace Input
{
	void Init()
	{
		g_InputState = 0;
		g_PrevInputState = 0;
	}

	void Update()
	{
		g_PrevInputState = g_InputState;

		g_InputState = 0;

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
	}

	void Draw()
	{

	}

	void Fin()
	{

	}

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
}