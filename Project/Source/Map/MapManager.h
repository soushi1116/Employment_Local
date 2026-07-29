#pragma once
#include "Map.h"
#include "MapImage.h"

class MapManager
{
public:
	MapManager();
	~MapManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new MapManager;
		}
	}

	static MapManager* GetInstance() { return m_Instance; }

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
	void DrawImage();
	void Fin();

public:
	void CreateMap();

	Map* GetMap() { return m_Map; }

private:
	static MapManager* m_Instance;

	Map* m_Map;

	MapImage* m_MapImage;
};

