#include "DxLib.h"
#include "MissionManager.h"
#include "MissionParameter.h"
#include "KillBaster.h"
#include "../Character/CharacterManager.h"
#include "../BattleManager/BattleManager.h"

const int MISSION_NUM_MAX = 4;
const int MISSION_CREATE_INTERVAL = 30 * 60;

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

void MissionManager::CreateMission(MissionType type)
{
	switch (type)
	{
	case KILL_BASTER:
	{
		KillBaster* killBaster = new KillBaster;

		killBaster->Init();
		killBaster->SetType(type);
		killBaster->Load();
		killBaster->Start();
		/*if (m_MissionNum % 2 == 0)
		{
			killBaster->SetReward(POWER_UP, 1.5f);
		}
		else
		{
			killBaster->SetReward(HP_HEAL, 50.0f);
		}*/

		killBaster->SetReward(DEFENCE_UP, 1.5f);

		m_MissionList.push_back(killBaster);

		m_MissionNum++;
		break;
	}
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}
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

	CreateMission(KILL_BASTER);
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
		CreateMission(KILL_BASTER);
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

	DrawFormatString(800, 400, GetColor(255, 255, 255), "timer:%d", m_MissionCreateTimer);
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
