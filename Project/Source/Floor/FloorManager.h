#pragma once
#include "Floor.h"

class FloorManager
{
public:
	FloorManager();
	~FloorManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new FloorManager;
		}
	}

	static FloorManager* GetInstance() { return m_Instance; }

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
	void CreateFloor();

	Floor* GetFloor() { return m_Floor; }

private:
	static FloorManager* m_Instance;

	Floor* m_Floor;
};

