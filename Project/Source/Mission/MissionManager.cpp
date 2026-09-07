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
		KillBaster* killbaster = new KillBaster;

		killbaster->Init();
		killbaster->SetType(type);
		killbaster->Load();
		killbaster->Start();

		m_MissionList.push_back(killbaster);

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
	m_MissionList.remove_if([this](const MissionBase* mission) {
		if (!mission) return true;

		if (!mission->IsActive())
		{
			m_MissionNum--;
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
