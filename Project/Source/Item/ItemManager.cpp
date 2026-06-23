#include "ItemManager.h"
#include "Coin.h"
#include "../MyMath/MyMath.h"

ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_TYPE_MAX; i++)
	{
		m_Item[i] = nullptr;
	}
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
}

void ItemManager::Update()
{
	for (auto& item : m_ItemList)
	{
		item->Update();
	}
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