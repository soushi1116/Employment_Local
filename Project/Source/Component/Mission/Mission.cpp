#include "Mission.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../Timer/Timer.h"
#include "../../Managers/BattleManager/BattleManager.h"
#include "../../Managers/CharacterManager/CharacterManager.h"
#include "../../Sound/SoundManager.h"

constexpr int MISSION_UI_BLINK_SPEED = 10;

Mission::Mission(GameObject* owner)
	: Component(owner)
	, m_MissionType(MISSION_TYPE_NONE)
	, m_RewardType(REWARD_TYPE_NONE)
	, m_Timer(m_Owner->GetComponent<Timer>())
	, m_BordarNum(0)
	, m_CurrnetNum(0)
	, m_IsArchived(false)
	, m_IsOverTime(false)
	, m_OriginNum(0)
{

}

Mission::~Mission()
{
	
}

void Mission::Start()
{
	switch (m_MissionType)
	{
	case DAMAGE:
		m_OriginNum = BattleManager::GetInstance()->GetDamageAmount();
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}
	
}

void Mission::Step()
{
	Mission::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	int totalNum = 0;

	switch (m_MissionType)
	{
	case DAMAGE:
		totalNum = BattleManager::GetInstance()->GetDamageAmount();
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}

	m_CurrnetNum = totalNum - m_OriginNum;

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

	auto sound = SoundManager::GetInstance()->GetSound();

	// ミッション達成・プレイヤーを強化
	if (m_IsArchived)
	{
		auto playerObj = CharacterManager::GetInstance()->GetPlayer();
		auto playerParameter = playerObj->GetComponent<CharacterParameter>();
		auto playerMove = playerObj->GetComponent<CharacterMove>();

		playerParameter->AddSuperAttackPoint(100);

		switch (m_RewardType)
		{
		case HP_HEAL:
			playerMove->HPHeal(playerParameter->GetMaxHp() / 10);
			sound->PlaySE(SE_HP_HEAL);
			break;
		case POWER_UP:
			playerMove->CreateState(STATE_POWER_UP);
			sound->PlaySE(SE_POWER_UP);
			break;
		case DEFENCE_UP:
			playerMove->CreateState(STATE_DEFENCE_UP);
			sound->PlaySE(SE_POWER_UP);
			break;
		case SPEED_UP:
			playerMove->CreateState(STATE_SPEED_UP);
			sound->PlaySE(SE_POWER_UP);
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
		auto bossObj = CharacterManager::GetInstance()->GetBoss();
		auto bossParameter = bossObj->GetComponent<CharacterParameter>();

		bossParameter->AddSuperAttackPoint(300);
	}
}

void Mission::Update()
{
	if (m_Timer.expired())
	{
		m_Timer = m_Owner->GetComponent<Timer>();
	}

	Mission::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	// 残り5秒以下になったら点滅
	if (sharedPtrs.timerShared->GetCurrentSecond() <= 5)
	{
		auto graphRenderer = sharedPtrs.graphShared->GetComponent<SpriteRenderer>();
		auto iconRenderer = sharedPtrs.iconShared->GetComponent<SpriteRenderer>();
		auto textRenderer = sharedPtrs.textShared->GetComponent<TextRenderer>();

		if (graphRenderer->GetBlinkState() == 0) graphRenderer->BlinkStart(MISSION_UI_BLINK_SPEED, true);
		if (iconRenderer->GetBlinkState() == 0) iconRenderer->BlinkStart(MISSION_UI_BLINK_SPEED, true);
		if (textRenderer->GetBlinkState() == 0) textRenderer->BlinkStart(MISSION_UI_BLINK_SPEED, true);
	}
	 
	// 残り時間がなくなったら消滅
	if (sharedPtrs.timerShared->IsCountEnd() || m_IsArchived)
	{
		m_Owner->SetActive(false);

		sharedPtrs.graphShared->SetActive(false);
		sharedPtrs.iconShared->SetActive(false);
		sharedPtrs.textShared->SetActive(false);
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