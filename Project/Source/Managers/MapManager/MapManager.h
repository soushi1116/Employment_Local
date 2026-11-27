#pragma once
#include <vector>
#include <memory>
#include <string>
#include "DxLib.h"
#include "../Singleton.h"
#include "../../MyEnums/MyEnums.h"

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

