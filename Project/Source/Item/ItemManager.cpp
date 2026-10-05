#include "ItemManager.h"
#include "Coin.h"
#include "../MyMath/MyMath.h"
#include "../Component/GameObject.h"
#include "../Component/AllComponents.h"
#include "../Scene/SceneManager.h"
#include "../Collision/CollisionManager.h"

const int ITEM_SPAWN_INTERVAL = 100;
const int ITEM_SPAWN_AREA_RANGE = 250;

ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_TYPE_MAX; i++)
	{
		m_Item[i] = nullptr;
	}

	m_SpawnTime = 0;
	m_CoinHandle = 0;
}

ItemManager::~ItemManager()
{
	Fin();
}

void ItemManager::Init()
{
	//CreateItem(COIN);

	for (auto& item : m_ItemList)
	{
		item->Init();
	}
}

void ItemManager::Load()
{
	m_CoinHandle = MV1LoadModel("Data/Item/Coin.x");

	for (auto& item : m_ItemList)
	{
		switch (item->GetType())
		{
		case COIN:
			item->Load(m_CoinHandle);
			break;
		default:
			break;
		}
	}
}

void ItemManager::Start()
{
	for (auto& item : m_ItemList)
	{
		item->Start();
	}
}

void ItemManager::Step()
{
	for (auto& item : m_ItemList)
	{
		item->Step();
	}

	m_SpawnTime++;
}

void ItemManager::Update()
{
	for (auto& item : m_ItemList)
	{
		item->Update();
	}

	if (m_SpawnTime > ITEM_SPAWN_INTERVAL)
	{
		//CreateItem(COIN);

		m_SpawnTime = 0;
	}

	DeleteItem();
}

void ItemManager::Draw()
{
	
}

void ItemManager::Fin()
{
	for (auto& item : m_ItemList)
	{
		delete item;
	}

	m_ItemList.clear();

	for (auto item : m_Item)
	{
		delete item;
	}

	MV1DeleteModel(m_CoinHandle);
}

std::shared_ptr<GameObject> ItemManager::CreateItem(ItemType type)
{
	auto item = std::make_shared<GameObject>();

	auto newPhysics = item->AddComponent<_3DPhysics>();

	VECTOR spanwPos = VGet(0.0f, 0.0f, 0.0f);
	spanwPos.x = (float)(GetRand(ITEM_SPAWN_AREA_RANGE) - ITEM_SPAWN_AREA_RANGE / 2);
	spanwPos.z = (float)(GetRand(ITEM_SPAWN_AREA_RANGE) - ITEM_SPAWN_AREA_RANGE / 2);

	newPhysics->SetPos(spanwPos);
	newPhysics->SetScale(MyMath::VecSame(0.025f));
	auto collision = new SphereCollision;
	newPhysics->SetCollision(collision);

	newPhysics->SetUseGravity(false);

	switch (type)
	{
	case COIN:
		item->AddComponent<ModelRenderer>("Data/Item/Coin.x");
		break;
	case ITEM_TYPE_MAX:
		break;
	case ITEM_TYPE_NONE:
		break;
	default:
		break;
	}

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(item);

	return item;
}

void ItemManager::DeleteItem()
{	
	m_ItemList.remove_if([](const ItemBase* item) { 
		if (!item) return true;

		if (!item->IsActive())
		{
			delete item;
			return true;
		}
		return false;
	});
	
}

ItemBase* ItemManager::GetItem(ItemType type)
{
	for (auto item : m_ItemList)
	{
		if (item != nullptr && item->GetType() == type)
		{
			return item;
		}
	}
	return nullptr;
}