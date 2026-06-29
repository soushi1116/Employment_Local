#include "DxLib.h"
#include "MissionManager.h"
#include "Mission.h"
#include "MissionParameter.h"

const int MISSION_NUM_MAX = 4;

MissionManager* MissionManager::m_Instance = nullptr;

MissionManager::MissionManager()
{
	for (int i = 0; i < MISSION_TYPE_MAX; i++)
	{
		m_Mission[i] = nullptr;
	}
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
	for (auto mission : m_MissionList)
	{
		mission->Update();
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
