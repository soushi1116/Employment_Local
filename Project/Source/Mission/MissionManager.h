#pragma once
#include "Mission.h"
#include <vector>

class MissionManager
{
public:
	MissionManager();
	~MissionManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new MissionManager;
		}
	}

	static MissionManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void CreateMission(MissionType type);
	Mission* GetMission(MissionType type);
	Mission* GetSelectedMission();
	std::vector<Mission*> GetMissionList() { return m_MissionList; }

private:
	static MissionManager* m_Instance;

	Mission* m_Mission[MISSION_TYPE_MAX];

	std::vector<Mission*> m_MissionList;

	int m_SelectedNum;

	
};

