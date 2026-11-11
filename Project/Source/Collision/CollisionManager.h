#pragma once
#include "../Component/GameObject.h"
#include "../Component/Component.h"

class Physics3D;
class DamageCollision;

const int COLLISION_MAX = 128;

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
	void CheckCollision();

	void AddDamageCollision(std::shared_ptr<DamageCollision> collision) { m_DamageCollisions.push_back(collision); }

private:
	void CheckCharacterStage();
	void CheckCharacterCharacter();
	void CheckCharacterDamage();

private:
	static CollisionManager* m_Instance;

	std::vector<std::shared_ptr<DamageCollision>> m_DamageCollisions;
};

