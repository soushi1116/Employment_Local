#include "InputManager.h"
#include "PlayerInput.h"

InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{
	for (int i = 0; i < INPUT_TYPE_MAX; i++)
	{
		m_Input[i] = nullptr;
	}
}

InputManager::~InputManager()
{

}

void InputManager::CreateInput(InputType type)
{
	switch (type)
	{
	case PLAYER_INPUT:
		break;
	case NPC_INPUT:
		break;
	case NETWARK_INPUT:
		break;
	case INPUT_TYPE_MAX:
		break;
	case INPUT_TYPE_NONE:
		break;
	default:
		break;
	}
}