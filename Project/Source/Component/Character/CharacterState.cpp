#include "CharacterState.h"
#include "../Component.h"
#include "../GameObject.h"

CharacterState::CharacterState(GameObject* owner) : Component(owner)
{
	m_Active = false;
	m_Type = STATE_TYPE_NONE;
}

CharacterState::~CharacterState()
{

}

void CharacterState::Start()
{
	
}

void CharacterState::Update()
{
	if (!m_Active) return;

	if (auto timerPtr = m_Timer.lock())
	{
		if (timerPtr->IsCountEnd())
		{
			m_Active = false;
		}
	}
}

void CharacterState::SetIconPos(VECTOR pos)
{
	if (auto iconShared = m_IconRenderer.lock())
	{
		iconShared->SetPos(pos);
	}
}