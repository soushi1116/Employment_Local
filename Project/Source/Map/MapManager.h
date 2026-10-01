#pragma once
#include "MapBase.h"
#include "MapImage.h"
#include "MapParameter.h"
#include <vector>
#include <memory>

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
	std::shared_ptr<GameObject> CreateMap(MapType type);

private:
	static MapManager* m_Instance;
};

