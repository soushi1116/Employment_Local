#include "DxLib.h"
#include "MissionManager.h"
#include "MissionParameter.h"
#include "../Character/CharacterManager.h"
#include "../BattleManager/BattleManager.h"

const int MISSION_NUM_MAX = 4;
const int MISSION_CREATE_INTERVAL = 15 * 60;

MissionManager* MissionManager::m_Instance = nullptr;

MissionManager::MissionManager()
{
	for (int i = 0; i < MISSION_TYPE_MAX; i++)
	{
		m_Mission[i] = nullptr;
	}

	m_MissionNum = 0;

	m_MissionCreateTimer = MISSION_CREATE_INTERVAL;
}

MissionManager::~MissionManager()
{
	Fin();
}

void MissionManager::CreateMission()
{
	MissionType type = GetRandomType();

	MissionBase* mission = new MissionBase;

	mission->Init();
	mission->SetType(type);
	mission->Load();
	mission->Start();

	mission->SetRandomReward();

	m_MissionList.push_back(mission);

	m_MissionNum++;

}

void MissionManager::Init()
{
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

	int rewardIcon = 0;
	for (int i = 0; i < STATE_TYPE_MAX; i++)
	{
		switch (i)
		{
		case 0:
			rewardIcon = LoadGraph("Data/UI/battleScene/HealIcon.png");
			break;
		case 1:
			rewardIcon = LoadGraph("Data/UI/battleScene/PowerUpIcon.png");
			break;
		case 2:
			rewardIcon = LoadGraph("Data/UI/battleScene/DefenceUpIcon.png");
			break;
		default:
			break;
		}
		m_RewardIconList.push_back(rewardIcon);
	}
}

void MissionManager::Start()
{
	for (auto mission : m_MissionList)
	{
		mission->Start();
	}

	CreateMission();
}


void MissionManager::Step()
{
	for (auto mission : m_MissionList)
	{
		mission->Step();
	}

	if (m_MissionNum < MISSION_NUM_MAX)
	{
		m_MissionCreateTimer--;
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
	}

	if (m_MissionCreateTimer <= 0)
	{
		CreateMission();
		m_MissionCreateTimer = MISSION_CREATE_INTERVAL;
	}

	DeleteMission();
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

void MissionManager::DeleteMission()
{
	UIManager* uiManager = UIManager::GetInstance();

	m_MissionList.remove_if([this, uiManager](const MissionBase* mission) {
		if (!mission) return true;

		if (!mission->IsActive())
		{
			m_MissionNum--;

			uiManager->DeleteUI(mission->GetNumText());

			delete mission;

			return true;
		}
		return false;
		});
}

MissionType MissionManager::GetRandomType()
{
	MissionType result = MISSION_TYPE_NONE;

	int random = GetRand(MISSION_TYPE_MAX -1);

	switch (random)
	{
	case 0:
		result = KILL_OPPONENT;
		break;
	default:
		break;
	}

	return result;
}

MissionBase* MissionManager::GetMission(MissionType type)
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

MissionBase* MissionManager::GetSelectedMission()
{
	for (auto mission : m_MissionList)
	{
		if (mission->IsSelected())
		{
			return mission;
		}
	}
	return nullptr;
}
