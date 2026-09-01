#include "DxLib.h"
#include "BattleManager.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"

const int TIME_LIMIT_SECOND = 180;

BattleManager* BattleManager::m_Instance = nullptr;

BattleManager::BattleManager()
{
	m_BossWin = false;
	m_ChildWin = false;

	m_TimerFrame = 0;
	m_TimerSecond = 0;
	m_TimerMinute = 0;

	m_NoDamageTimerFrame = 0;
	m_NoDamageTimerSecond = 0;
	m_NoMoveTimerFrame = 0;
	m_NoMoveTimerSecond = 0;

	m_SuperAttackNum = 0;

	m_killedNum = 0;
}

BattleManager::~BattleManager()
{
	Fin();
}


void BattleManager::Init()
{

}

void BattleManager::Load()
{

}

void BattleManager::Start()
{
	m_TimerSecond = TIME_LIMIT_SECOND;
}


void BattleManager::Step()
{
	m_TimerFrame++;
	//m_NoDamageTimerFrame++;
	//m_NoMoveTimerFrame++;

	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	if (m_TimerFrame >= 60)
	{
		if (!m_BossWin && !m_ChildWin) 
		{
			m_TimerSecond--;
			m_TimerFrame = 0;

			for (auto character : characterList)
			{
				character->AddSkillPoint();

				if (character->IsBoss())
				{
					m_killedNum = character->GetKilledNum();
				}
			}
		}
	}

	if (m_TimerSecond >= 60)
	{
		m_TimerMinute++;
		m_TimerSecond -= 60;
	}

	if (m_TimerSecond < 0)
	{
		m_TimerMinute--;
		m_TimerSecond += 60;
	}

	if (m_TimerMinute <= 0 && m_TimerSecond <= 0)
	{
		BossWin();
	}

	/*if (m_NoDamageTimerFrame >= 60)
	{
		m_NoDamageTimerSecond++;
		m_NoDamageTimerFrame = 0;
	}

	if (m_NoMoveTimerFrame >= 60)
	{
		m_NoMoveTimerSecond++;
		m_NoMoveTimerFrame = 0;
	}	*/
}

void BattleManager::Update()
{
	
}

void BattleManager::Draw()
{
	//CharacterBase* player = CharacterManager::GetInstance()->SearchPlayer();

	DrawFormatString(1300, 200, GetColor(0, 0, 0), "%02d:%02d", m_TimerMinute, m_TimerSecond, TRUE);
	
	/*if (player->IsBoss())
	{
		Mission* selectedMission = MissionManager::GetInstance()->GetSelectedMission();

		MissionType selectedMissionType = selectedMission->GetType();

		switch (selectedMissionType)
		{
		case _3_MINUTE:
			DrawFormatString(1300, 200, GetColor(255, 255, 255), "%02d:%02d", m_TimerMinute, m_TimerSecond, TRUE);
			break;
		case _30_SECOND_NO_DAMAGE:
			DrawFormatString(1300, 200, GetColor(255, 255, 255), "NoDamage:%02d", m_NoDamageTimerSecond, TRUE);
			break;
		case _30_SECOND_NO_MOVE:
			DrawFormatString(1300, 200, GetColor(255, 255, 255), "NoMove%02d", m_NoMoveTimerSecond, TRUE);
			break;
		case KILL_10:
			DrawFormatString(1300, 200, GetColor(255, 255, 255), "KillNum%02d", m_killedNum, TRUE);
			break;
		case SUPER_ATTACK_5:
			break;
		case MISSION_TYPE_MAX:
			break;
		case MISSION_TYPE_NONE:
			break;
		default:
			break;
		}
	}*/
}

void BattleManager::Fin()
{
	
}


