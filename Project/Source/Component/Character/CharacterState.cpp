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

	auto timerShared = m_Timer.lock();
	auto rendererShared = m_IconRenderer.lock();
	auto parameterShared = m_ParentParameter.lock();

	if (!timerShared || !rendererShared || !parameterShared) return;

	if (timerShared->IsCountEnd())
	{
		m_Active = false;

		switch (m_Type)
		{
		case STATE_POWER_UP:
			parameterShared->AddPowerMagni(1.0f / 1.5f);
			break;
		case STATE_DEFENCE_UP:
			parameterShared->AddDefenceMagni(1.0f / 1.5f);
			break;
		case STATE_BOOST:
			parameterShared->AddPowerMagni(0.5f);
			parameterShared->AddDefenceMagni(2.0f);
			break;
		case STATE_SPEED_UP:
			parameterShared->AddSpeedMagni(1.0f / 1.5f);
			break;
		case STATE_POISONED:
			break;
		case STATE_INVISIBLE:
			break;
		case STATE_TYPE_MAX:
			break;
		case STATE_TYPE_NONE:
			break;
		default:
			break;
		}
	}

	if (timerShared->GetCurrentSecond() <= 5)
	{
		if (rendererShared->GetBlinkState() == 0)
		{
			rendererShared->BlinkStart(10, true);
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