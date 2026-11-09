#include "Mission.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Timer/Timer.h"

Mission::Mission(GameObject* owner) : Component(owner)
{
	m_MissionType = MISSION_TYPE_NONE;
	m_RewardType = REWARD_TYPE_NONE;

	m_Timer = m_Owner->GetComponent<Timer>();
}

Mission::~Mission()
{
	
}

void Mission::Update()
{
	if (m_Timer.expired())
	{
		m_Timer = m_Owner->GetComponent<Timer>();
	}

	std::shared_ptr<Timer> timerShared = m_Timer.lock();

	if (!timerShared) return;
	 
	if (timerShared->IsCountEnd())
	{
		m_Owner->SetActive(false);

		auto graphShared = m_Graph.lock();
		auto textShared = m_Text.lock();

		if (!graphShared || !textShared) return;

		graphShared->SetActive(false);
		textShared->SetActive(false);
	}
}