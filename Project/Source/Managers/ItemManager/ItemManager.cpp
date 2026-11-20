#include "ItemManager.h"
#include "../../MyMath/MyMath.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"
#include "../../Scene/SceneManager.h"
#include "../CollisionManager/CollisionManager.h"

constexpr int ITEM_SPAWN_INTERVAL = 100;
constexpr int ITEM_SPAWN_AREA_RANGE = 250;

ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
	:m_SpawnTime(0)
{

}

ItemManager::~ItemManager()
{
	Fin();
}

void ItemManager::Init()
{
	
}

void ItemManager::Load()
{
	
}

void ItemManager::Start()
{
	
}

void ItemManager::Step()
{
	m_SpawnTime++;
}

void ItemManager::Update()
{
	if (m_SpawnTime > ITEM_SPAWN_INTERVAL)
	{
		CreateItem(COIN);

		m_SpawnTime = 0;
	}
}

void ItemManager::Draw()
{

}

void ItemManager::Fin()
{
	
}

std::shared_ptr<GameObject> ItemManager::CreateItem(ItemType type)
{
	auto itemObj = std::make_shared<GameObject>();
	itemObj->AddTag(TAG_ITEM);

	auto newPhysics = itemObj->AddComponent<Physics3D>();

	VECTOR spanwPos = VGet(0.0f, 0.0f, 0.0f);
	spanwPos.x = (float)(GetRand(ITEM_SPAWN_AREA_RANGE) - ITEM_SPAWN_AREA_RANGE / 2);
	spanwPos.z = (float)(GetRand(ITEM_SPAWN_AREA_RANGE) - ITEM_SPAWN_AREA_RANGE / 2);

	newPhysics->SetPos(spanwPos);
	newPhysics->SetScale(MyMath::VecSame(0.025f));
	auto collision = itemObj->AddComponent<SphereCollision>();
	newPhysics->SetCollision(collision);

	newPhysics->SetUseGravity(false);

	switch (type)
	{
	case COIN:
	{
		itemObj->AddComponent<ModelRenderer>("Data/Item/Coin.x");
		auto coinCmp = itemObj->AddComponent<Coin>();
		coinCmp->SetRewardPoint(300);
		coinCmp->SetType(COIN);
		break;
	}
	case ITEM_TYPE_MAX:
		break;
	case ITEM_TYPE_NONE:
		break;
	default:
		break;
	}

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(itemObj);

	return itemObj;
}

