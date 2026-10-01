#include "MapManager.h"
#include "../Component/AllComponents.h"

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
	auto mapCollision = std::make_shared<GameObject>();
	auto mapTransform = map->AddComponent<Transform>();
	mapTransform->SetPos(MyMath::VecY(-10.0f));
	auto mapCollisionTransform = mapCollision->AddComponent<Transform>();
	mapCollisionTransform->SetPos(MyMath::VecY(-10.0f));

	switch (type)
	{
	case MAP_TEST:
		map->AddComponent<ModelRenderer>("Data/Map/Test/TestStage.x");
		break;
	case MAP_FACTORY:
		map->AddComponent<ModelRenderer>("Data/Map/Factory/Factory.x");
		break;
	case MAP_FOREST:
		map->AddComponent<ModelRenderer>("Data/Map/Forest/Forest.x");
		break;
	case MAP_TYPE_MAX:
		break;
	case MAP_TYPE_NONE:
		break;
	default:
		break;
	}

	return map;
}