#pragma once
#include "MissionBase.h"
#include <list>

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
	void DeleteMission();
	MissionBase* GetMission(MissionType type);
	MissionBase* GetSelectedMission();
	std::list<MissionBase*> GetMissionList() { return m_MissionList; }

private:
	static MissionManager* m_Instance;

	MissionBase* m_Mission[MISSION_TYPE_MAX];

	std::list<MissionBase*> m_MissionList;

	int m_MissionNum;

	int m_MissionCreateTimer;
};

