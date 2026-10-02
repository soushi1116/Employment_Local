#include "MapManager.h"
#include "../Component/AllComponents.h"
#include "../Collision/CollisionManager.h"

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
	auto mapTransform = map->AddComponent<Transform>();
	mapTransform->SetPos(MyMath::VecY(-10.0f));
	auto collider = map->AddComponent<Collider>();
	CollisionManager::GetInstance()->SetUpCollision(collider, MESH_COLLISION);
	auto collision = collider->GetCollison<MeshCollision>();

	switch (type)
	{
	case MAP_TEST:
		map->AddComponent<ModelRenderer>("Data/Map/Test/TestStage.x");
		collision->SetCollisionHandle("Data/Map/Test/TestStageCollision.x");
		break;
	case MAP_FACTORY:
		map->AddComponent<ModelRenderer>("Data/Map/Factory/Factory.x");
		collision->SetCollisionHandle("Data/Map/Factory/FactoryCollision.x");
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

	return map;
}