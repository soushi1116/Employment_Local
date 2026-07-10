#pragma once

class CollisionAABB;
class CollisionSphere;

const int COLLISION_MAX = 64;

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
	void DeleteAABB(CollisionAABB* targetAABB);

	CollisionSphere* CreateSphere();
	void DeleteSphere(CollisionSphere* targetSphere);

public:
	void CheckCollision();

private:
	void CheckCharacterFloor();
	void CheckCharacterBullet();

private:
	static CollisionManager* m_Instance;

	CollisionAABB* m_AABB[COLLISION_MAX];
	CollisionSphere* m_Sphere[COLLISION_MAX];
};

