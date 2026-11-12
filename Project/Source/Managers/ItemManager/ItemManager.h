#pragma once
#include <vector>
#include <memory>
#include "../Singleton.h"

const int ITEM_MAX_NUM = 32;

class GameObject;

class ItemManager : public Singleton<ItemManager>
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
	std::shared_ptr<GameObject> CreateItem(ItemType type);

private:
	static ItemManager* m_Instance;

	std::vector<GameObject> m_Items;

	int m_SpawnTime;
};
