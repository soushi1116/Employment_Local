#include "MapManager.h"
#include "TestMap.h"
#include "Factory.h"
#include "Forest.h"

MapManager* MapManager::m_Instance = nullptr;

MapManager::MapManager()
{
	m_Map = nullptr;

	m_MapImage = nullptr;

	m_MapType = MAP_TYPE_NONE;
}

MapManager::~MapManager()
{
	Fin();
}

void MapManager::SetMapType(MapType type)
{
	m_MapType = type;
	for (auto& map : m_MapList)
	{
		if (map->GetType() == type)
		{
			m_Map = map;
		}
	}

	if (m_Map == nullptr)
	{
		MapBase* map = CreateMap(m_MapType);
		m_Map = map;
	}
}

MapBase* MapManager::CreateMap(MapType type)
{
	VECTOR mapScale = {};

	MapBase* createdMap = nullptr;

	switch (type)
	{
	case MAP_TEST:
	{
		TestMap* test = new TestMap;

		test->Init();
		test->Load();
		test->Start();

		mapScale = test->GetScale();

		createdMap = test;
		break;
	}
		break;
	case MAP_FACTORY:
	{
		Factory* factory = new Factory;

		factory->Init();
		factory->Load();
		factory->Start();

		mapScale = factory->GetScale();

		createdMap = factory;
		break;
	}
	case MAP_FOREST:
	{
		Forest* forest = new Forest;

		forest->Init();
		forest->Load();
		forest->Start();

		mapScale = forest->GetScale();

		createdMap = forest;
		break;
	}
	case MAP_TYPE_MAX:
		break;
	case MAP_TYPE_NONE:
		break;
	default:
		break;
	}

	if (!m_MapImage)
	{
		m_MapImage = new MapImage;
		m_MapImage->Init();
		m_MapImage->Load();
		m_MapImage->Start();
		m_MapImage->SetScale(mapScale);
	}

	m_MapList.push_back(createdMap);

	return createdMap;
}

void MapManager::Init()
{
	if (m_Map)
	{
		m_Map->Init();
	}
}

void MapManager::Load()
{
	if (m_Map)
	{
		m_Map->Load();
	}

	if (m_MapImage)
	{
		m_MapImage->Load();
	}
}

void MapManager::Start()
{
	if (m_Map)
	{
		m_Map->Start();
	}

	if (m_MapImage)
	{
		m_MapImage->Start();
	}
}

void MapManager::Step()
{
	if (m_Map)
	{
		m_Map->Step();
	}

	if (m_MapImage)
	{
		m_MapImage->Step();
	}
}

void MapManager::Update()
{
	if (m_Map)
	{
		m_Map->Update();
	}

	if (m_MapImage)
	{
		m_MapImage->Update();
	}
}

void MapManager::Draw()
{
	if (m_Map)
	{
		m_Map->Draw();
	}
}

void MapManager::DrawImage()
{
	if (m_MapImage)
	{
		m_MapImage->Draw();
	}
}

void MapManager::Fin()
{
	if (m_Map)
	{
		delete m_Map;
	}

	m_MapImage->Fin();
}

MapBase* MapManager::GetMap(MapType type)
{
	for (auto map : m_MapList)
	{
		if (map != nullptr && map->GetType() == type)
		{
			return map;
		}
	}
	return nullptr;
}
