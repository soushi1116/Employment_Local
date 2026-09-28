#include "InputManager.h"
#include "PlayerInput.h"
#include "NPCInput.h"

InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{
	for (int i = 0; i < CHARACTER_INPUT_TYPE_MAX; i++)
	{
		m_Input[i] = nullptr;
	}
}

InputManager::~InputManager()
{

}

void InputManager::CreateInput(InputType type)
{
	for (int i = 0; i < CHARACTER_INPUT_TYPE_MAX; i++)
	{
		// ‚·‚Å‚É¶¬‚³‚ê‚Ä‚¢‚½‚çŽŸ‚Ì˜g
		if (m_Input[i] != nullptr) continue;

		switch (type)
		{
		case INPUT_TYPE_PLAYER:
			m_Input[i] = new PlayerInput;
			break;
		case INPUT_TYPE_NPC:
			m_Input[i] = new NPCInput;
			break;
		case INPUT_TYPE_NETWORK:
			break;
		case INPUT_TYPE_MAX:
			break;
		case INPUT_TYPE_NONE:
			break;
		default:
			break;
		}

		// ¶¬‚Å‚«‚½‚çI—¹
		if (m_Input[i] != nullptr) break;
	}
}