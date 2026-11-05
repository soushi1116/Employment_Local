#pragma once
#include <vector>
#include <memory>
#include <string>
#include "DxLib.h"
#include "../Singleton.h"

enum MapType
{
	MAP_TEST,
	MAP_FACTORY,
	MAP_FOREST,

	MAP_TYPE_MAX,
	MAP_TYPE_NONE = -1
};

class GameObject;

class MapManager : public Singleton<MapManager>
{
public:
	MapManager();
	~MapManager();

public:
	std::shared_ptr<GameObject> CreateMap(MapType type);
	std::weak_ptr<GameObject> GetCurrentMap() { return m_CurrentMap; }

	std::vector<VECTOR> LoadNodeData(const std::string& filePath);

private:
	static MapManager* m_Instance;
	std::weak_ptr<GameObject> m_CurrentMap;
};

