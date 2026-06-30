#include "DxLib.h"
#include "MissionManager.h"
#include "Mission.h"
#include "MissionParameter.h"
#include "../Character/CharacterManager.h"
#include "../BattleManager/BattleManager.h"

const int MISSION_NUM_MAX = 4;

MissionManager* MissionManager::m_Instance = nullptr;

MissionManager::MissionManager()
{
	for (int i = 0; i < MISSION_TYPE_MAX; i++)
	{
		m_Mission[i] = nullptr;
	}

	m_SelectedNum = 0;
}

MissionManager::~MissionManager()
{
	Fin();
}

void MissionManager::CreateMission(MissionType type)
{
	Mission* mission = new Mission;

	mission->SetType(type);

	m_MissionList.push_back(mission);
}

void MissionManager::Init()
{
	CreateMission(_3_MINUTE);
	CreateMission(_30_SECOND_NO_DAMAGE);
	CreateMission(_30_SECOND_NO_MOVE);
	CreateMission(KILL_10);

	for (auto mission : m_MissionList)
	{
		mission->Init();
	}
}

void MissionManager::Load()
{
	for (auto mission : m_MissionList)
	{
		mission->Load();
	}
}

void MissionManager::Start()
{
	for (auto mission : m_MissionList)
	{
		mission->Start();
	}
}


void MissionManager::Step()
{
	for (auto mission : m_MissionList)
	{
		mission->Step();
	}
}

void MissionManager::Update()
{
	BattleManager* battleManager = BattleManager::GetInstance();
	int minute = battleManager->GetMinute();
	int superAttackNum = battleManager->GetSuperAttackNum();
	int killedNum = battleManager->GetKilledNum();
	int noDamageTimer = battleManager->GetNoDamageTimer();
	int noMoveTimer = battleManager->GetNoMoveTimer();

	for (auto mission : m_MissionList)
	{
		mission->Update();

		switch (mission->GetType())
		{
		case _3_MINUTE:
			if (minute >= 3)
			{
				mission->Achieve();
			}
			break;

		case _30_SECOND_NO_DAMAGE:
			if (noDamageTimer >= 30)
			{
				mission->Achieve();
			}
			break;

		case _30_SECOND_NO_MOVE:
			if (noMoveTimer >= 30)
			{
				mission->Achieve();
			}
			break;

		case KILL_10:
			if (killedNum >= 10)
			{
				mission->Achieve();
			}
			break;

		case SUPER_ATTACK_5:
			if (superAttackNum >= 5)
			{
				mission->Achieve();
			}
			break;

		default:
			break;
		}

		if (mission->IsSelected() && mission->IsAchieved())
		{
			battleManager->ParentWin();
		}
	}
}

void MissionManager::Draw()
{
	int index = 0;

	for (auto mission : m_MissionList)
	{
		mission->Draw(index);

		index++;
	}
}

void MissionManager::Fin()
{
	for(auto& mission : m_MissionList)
	{
		delete mission;
	}

	m_MissionList.clear();

	for (auto mission : m_Mission)
	{
		delete mission;
	}
}

Mission* MissionManager::GetMission(MissionType type)
{
	for (auto mission : m_MissionList)
	{
		if (mission != nullptr && mission->GetType() == type)
		{
			return mission;
		}
	}
	return nullptr;
}
