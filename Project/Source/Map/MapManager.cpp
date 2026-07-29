#include "MapManager.h"

MapManager* MapManager::m_Instance = nullptr;

MapManager::MapManager()
{
	m_Map = nullptr;
	m_MapImage = nullptr;
}

MapManager::~MapManager()
{
	Fin();
}

void MapManager::CreateMap()
{
	VECTOR mapScale = {};

	if (!m_Map)
	{
		m_Map = new Map;
		m_Map->Init();
		m_Map->Load();
		m_Map->Start();

		mapScale = m_Map->GetScale();
	}

	if (!m_MapImage)
	{
		m_MapImage = new MapImage;
		m_MapImage->Init();
		m_MapImage->Load();
		m_MapImage->Start();
		m_MapImage->SetScale(mapScale);
	}
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
	m_Map->Fin();
	m_MapImage->Fin();
}


