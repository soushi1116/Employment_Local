#include "NPCInput.h"

NPCInput::NPCInput(GameObject* owner) : InputBase(owner)
{
	m_Type = INPUT_TYPE_NPC;
}

NPCInput::~NPCInput()
{

}