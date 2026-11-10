#include "Mission.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Timer/Timer.h"
#include "../../Managers/BattleManager/BattleManager.h"

Mission::Mission(GameObject* owner) : Component(owner)
{
	m_MissionType = MISSION_TYPE_NONE;
	m_RewardType = REWARD_TYPE_NONE;

	m_Timer = m_Owner->GetComponent<Timer>();

	m_BordarNum = 0;
	m_CurrnetNum = 0;
	m_IsArchived = false;

	m_OriginKilledNum = 0;
}

Mission::~Mission()
{
	
}

void Mission::Start()
{
	m_OriginKilledNum = BattleManager::GetInstance()->GetKilledNum();
}

void Mission::Step()
{
	int totalNum = 0;

	switch (m_MissionType)
	{
	case KILL_OPPONENT:
		totalNum = BattleManager::GetInstance()->GetKilledNum();
		m_CurrnetNum = totalNum - m_OriginKilledNum;
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}

	if (m_CurrnetNum >= m_BordarNum)
	{
		m_IsArchived = true;
	}

	auto textSharedObj = m_Text.lock();

	if (!textSharedObj) return;

	auto textSharedCmp = textSharedObj->GetComponent<TextRenderer>();

	char numText[8];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrnetNum, m_BordarNum);

	textSharedCmp->SetText(numText);

	auto bossShared = m_Boss.lock();

	if (!bossShared) return;

	auto bossParameter = bossShared->GetComponent<CharacterParameter>();
	auto bossMove = bossShared->GetComponent<CharacterMove>();

	if (!bossParameter || !bossMove) return;

	if (m_IsArchived)
	{
		switch (m_RewardType)
		{
		case HP_HEAL:
			bossParameter->IncreaseHP(50);
			break;
		case POWER_UP:
			bossParameter->AddPowerMagni(1.5f);
			bossMove->CreateState(STATE_POWER_UP);
			break;
		case DEFENCE_UP:
			bossParameter->AddDefenceMagni(1.5f);
			bossMove->CreateState(STATE_DEFENCE_UP);
			break;
		case REWARD_TYPE_MAX:
			break;
		case REWARD_TYPE_NONE:
			break;
		default:
			break;
		}
	}
}

void Mission::Update()
{
	if (m_Timer.expired())
	{
		m_Timer = m_Owner->GetComponent<Timer>();
	}

	std::shared_ptr<Timer> timerShared = m_Timer.lock();

	if (!timerShared) return;
	 
	if (timerShared->IsCountEnd() || m_IsArchived)
	{
		m_Owner->SetActive(false);

		auto graphShared = m_Graph.lock();
		auto iconShared = m_Icon.lock();
		auto textShared = m_Text.lock();

		if (!graphShared || !textShared || !iconShared) return;

		graphShared->SetActive(false);
		iconShared->SetActive(false);
		textShared->SetActive(false);
	}

	
}