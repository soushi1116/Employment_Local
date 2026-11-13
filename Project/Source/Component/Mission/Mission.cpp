#include "Mission.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Timer/Timer.h"
#include "../../Managers/BattleManager/BattleManager.h"
#include "../../Managers/CharacterManager/CharacterManager.h"

Mission::Mission(GameObject* owner) : Component(owner)
{
	m_MissionType = MISSION_TYPE_NONE;
	m_RewardType = REWARD_TYPE_NONE;

	m_Timer = m_Owner->GetComponent<Timer>();

	m_BordarNum = 0;
	m_CurrnetNum = 0;
	m_IsArchived = false;
	m_IsOverTime = false;

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
	Mission::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

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

	if (sharedPtrs.timerShared->IsCountEnd())
	{
		m_IsOverTime = true;
	}

	auto textSharedCmp = sharedPtrs.textShared->GetComponent<TextRenderer>();

	char numText[8];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrnetNum, m_BordarNum);

	textSharedCmp->SetText(numText);

	if (m_IsArchived)
	{
		auto bossObj = CharacterManager::GetInstance()->GetBoss();
		auto bossParameter = bossObj->GetComponent<CharacterParameter>();
		auto bossMove = bossObj->GetComponent<CharacterMove>();

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
		case SPEED_UP:
			bossParameter->AddSpeedMagni(1.5f);
			bossMove->CreateState(STATE_SPEED_UP);
			break;
		case REWARD_TYPE_MAX:
			break;
		case REWARD_TYPE_NONE:
			break;
		default:
			break;
		}
	}

	if (m_IsOverTime)
	{
		const auto& characters = CharacterManager::GetInstance()->GetCharacters();

		for (const auto& character : characters)
		{
			const auto& characterShared = character.lock();

			if (!characterShared) continue;

			auto characterParameter = characterShared->GetComponent<CharacterParameter>();
			auto characterMove= characterShared->GetComponent<CharacterMove>();

			if (characterParameter->IsBoss()) continue;

			switch (m_RewardType)
			{
			case HP_HEAL:
				characterParameter->IncreaseHP(50);
				break;
			case POWER_UP:
				characterParameter->AddPowerMagni(1.5f);
				characterMove->CreateState(STATE_POWER_UP);
				break;
			case DEFENCE_UP:
				characterParameter->AddDefenceMagni(1.5f);
				characterMove->CreateState(STATE_DEFENCE_UP);
				break;
			case SPEED_UP:
				characterParameter->AddSpeedMagni(1.5f);
				characterMove->CreateState(STATE_SPEED_UP);
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
}

void Mission::Update()
{
	if (m_Timer.expired())
	{
		m_Timer = m_Owner->GetComponent<Timer>();
	}

	std::shared_ptr<Timer> timerShared = m_Timer.lock();

	if (!timerShared) return;

	if (timerShared->GetCurrentMinute() <= 5)
	{
		// “_–Å
	}
	 
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

Mission::SharedMembers Mission::CheckMemberPtrs()
{
	Mission::SharedMembers ptrs;

	ptrs.timerShared = m_Timer.lock();
	ptrs.graphShared = m_Graph.lock();
	ptrs.iconShared = m_Icon.lock();
	ptrs.textShared = m_Text.lock();

	if (!ptrs.timerShared || !ptrs.graphShared || !ptrs.iconShared || !ptrs.textShared)
	{
		ptrs.isSafety = false;
	}
	else
	{
		ptrs.isSafety = true;
	}

	return ptrs;
}