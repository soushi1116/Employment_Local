#pragma once
#include "../Component/GameObject.h"
#include "../Component/Component.h"

class CollisionAABB;
class CollisionSphere;
class _3DPhysics;

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
	void Draw();
	void Fin();

	void SetUpCollision(std::shared_ptr<_3DPhysics>, CollisionType type);

public:
	void CheckCollision();

private:
	void CheckCharacterStage();
	void CheckCharacterBullet();
	void CheckCharacterCharacter();
	void CheckCharacterAttack();
	void CheckCharacterSuperAttack();
	void CheckCameraStage();
	void CheckRooterStage();
	void CheckBulletStage();

private:
	static CollisionManager* m_Instance;

	CollisionAABB* m_AABB[COLLISION_MAX];
	CollisionSphere* m_Sphere[COLLISION_MAX];
};

