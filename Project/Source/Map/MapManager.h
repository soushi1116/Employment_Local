#pragma once
#include "MapBase.h"
#include "MapImage.h"
#include "MapParameter.h"
#include <vector>

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
	MapBase* CreateMap(MapType type);

	void SetMapType(MapType type);

	MapBase* GetMap(MapType type);

	MapBase* GetCurrentMap() { return m_Map; }

private:
	static MapManager* m_Instance;

	MapBase* m_Map;

	std::vector<MapBase*> m_MapList;

	MapType m_MapType;

	MapImage* m_MapImage;
};

