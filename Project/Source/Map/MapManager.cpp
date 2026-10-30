#include "MapManager.h"
#include "../Component/AllComponents.h"
#include "../Collision/CollisionManager.h"
#include "../Scene/SceneManager.h"
#include "../Component/GameObject.h"

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

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(map);

	m_CurrentMap = map;

	return map;
}