#include "MapManager.h"
#include "../../Component/AllComponents.h"
#include "../../Collision/CollisionManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Component/GameObject.h"
#include <fstream>
#include <sstream>
#include <algorithm>

MapManager* MapManager::m_Instance = nullptr;

MapManager::MapManager()
{
	
}

MapManager::~MapManager()
{
	
}

std::shared_ptr<GameObject> MapManager::CreateMap(MapType type)
{
	auto map = std::make_shared<GameObject>();
	map->AddTag(TAG_STAGE);

	auto newPhysics = map->AddComponent<Physics3D>();
	newPhysics->SetPos(MyMath::VecY(-10.0f));
	auto collision = map->AddComponent<MeshCollision>();
	newPhysics->SetCollision(collision);
	auto mapNode = map->AddComponent<MapNode>();
	std::vector<VECTOR> nodeData;

	newPhysics->SetUseGravity(false);

	switch (type)
	{
	case MAP_TEST:
		map->AddComponent<ModelRenderer>("Data/Map/Test/TestStage.x");
		collision->SetCollisionHandle("Data/Map/Test/TestStageCollision.x");
		break;
	case MAP_FACTORY:
		map->AddComponent<ModelRenderer>("Data/Map/Factory/Factory.x");
		collision->SetCollisionHandle("Data/Map/Factory/FactoryCollision.x");
		nodeData = LoadNodeData("Data/Parameters/FactoryNodePos.csv");
		break;
	case MAP_FOREST:
		map->AddComponent<ModelRenderer>("Data/Map/Forest/Forest.x");
		collision->SetCollisionHandle("Data/Map/Forest/ForestCollision.x");
		break;
	case MAP_TYPE_MAX:
		break;
	case MAP_TYPE_NONE:
		break;
	default:
		break;
	}

	if (!nodeData.empty())
	{
		mapNode->SetNodeData(nodeData);
	}

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(map);

	m_CurrentMap = map;

	return map;
}

/// <summary>
/// ノードデータの読み取り
/// </summary>
/// <param name="filePath">ファイル名</param>
/// <returns>読み取りできたかどうか</returns>
std::vector<VECTOR> MapManager::LoadNodeData(const std::string& filePath)
{
	std::vector<VECTOR> nodeData;

	std::ifstream file(filePath);
	if (!file.is_open()) return nodeData;

	std::string line;
	bool isFirstLine = true;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		// 1行目は無視
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		std::stringstream ss(line);
		std::string value;

		VECTOR currentNodeData = MyMath::VecZero();
		int index = 0;

		while (std::getline(ss, value, ','))
		{
			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

			// 1列目と3列目以降は無視
			if (index == 0 || index > 3)
			{
				index++;
				continue;
			}

			// 2列目をx座標に入力
			if (index == 1)
			{
				if (!value.empty())
				{
					try
					{
						currentNodeData.x = std::stof(value);
					}
					catch (const std::invalid_argument&)
					{
						currentNodeData.x = 0.0f;
					}
					catch (const std::out_of_range&)
					{
						currentNodeData.x = 0.0f;
					}
				}
			}

			// 3列目をz座標に入力
			if (index == 2)
			{
				if (!value.empty())
				{
					try
					{
						currentNodeData.z = std::stof(value);
					}
					catch (const std::invalid_argument&)
					{
						currentNodeData.z = 0.0f;
					}
					catch (const std::out_of_range&)
					{
						currentNodeData.z = 0.0f;
					}
				}
			}

			index++;
		}

		// 2列目まで読み取れていれば追加
		if (index >= 2)
		{
			nodeData.push_back(currentNodeData);
		}
	}
	return nodeData;
}