#pragma once
#include "Dxlib.h"
#include "InputBase.h"
#include "InputParameter.h"

class InputBase;
class PlayerInput;

class InputManager
{
public:
	InputManager();
	~InputManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new InputManager;
		}
	}

	static InputManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Update();

	InputBase* CreateInput(InputType type);
	void ClearInput();

	InputBase* GetInput(CharacterInputType type) { return m_Input[type]; }

private:
	static InputManager* m_Instance;
	InputBase* m_Input[CHARACTER_INPUT_TYPE_MAX];
};

