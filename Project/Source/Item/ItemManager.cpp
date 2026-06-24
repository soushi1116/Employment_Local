#include "ItemManager.h"
#include "Coin.h"
#include "../MyMath/MyMath.h"

const int ITEM_SPAWN_INTERVAL = 600;

ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_TYPE_MAX; i++)
	{
		m_Item[i] = nullptr;
	}

	m_SpawnTime = 0;
}

ItemManager::~ItemManager()
{
	Fin();
}

void ItemManager::Init()
{
	CreateItem(COIN);

	for (auto& item : m_ItemList)
	{
		item->Init();
	}
}

void ItemManager::Load()
{
	for (auto& item : m_ItemList)
	{
		item->Load();
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
		CreateItem(COIN);

		m_SpawnTime = 0;
	}

	DeleteItem();
}

void ItemManager::Draw()
{
	for (auto& item : m_ItemList)
	{
		item->Draw();
	}

	SetUseLighting(TRUE);
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
}

void ItemManager::CreateItem(ItemType type)
{
	switch (type)
	{
	case COIN:
	{
		Coin* newCoin = new Coin;

		VECTOR spanwPos = VGet(0.0f, 0.0f, 0.0f);
		spanwPos.x = (float)(GetRand(100) - 50);
		spanwPos.z = (float)(GetRand(100) - 50);

		newCoin->SetPos(spanwPos);

		newCoin->Init();
		newCoin->Load();
		newCoin->Start();

		m_ItemList.push_back(newCoin);
	}
	break;
	case ITEM_TYPE_MAX:
		break;
	case ITEM_TYPE_NONE:
		break;
	default:
		break;
	}
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