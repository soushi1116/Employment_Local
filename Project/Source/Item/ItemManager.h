#pragma once
#include "ItemBase.h"
#include "ItemParameter.h"
#include <list>

const int ITEM_MAX_NUM = 32;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new ItemManager;
		}
	}

	static ItemManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void CreateItem(ItemType type);
	ItemBase* GetItem(ItemType type);
	std::list<ItemBase*> GetItemList() { return m_ItemList; }

private:
	static ItemManager* m_Instance;

	ItemBase* m_Item[ITEM_TYPE_MAX];

	std::list<ItemBase*> m_ItemList;
};
