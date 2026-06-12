#pragma once
#include <vector>

class CollisionAABB;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new CollisionManager;
		}
	}

	static CollisionManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Draw();
	void Fin();

	CollisionAABB* CreateAABB();

public:

private:
	static CollisionManager* m_Instance;
	std::vector<CollisionAABB*> m_AABB;
};

