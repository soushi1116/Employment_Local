#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Character/CharacterManager.h"
#include "../Floor/FloorManager.h"

CollisionManager* CollisionManager::m_Instance = nullptr;

CollisionManager::CollisionManager()
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		m_AABB[i] = nullptr;
		m_Sphere[i] = nullptr;
	}
}

CollisionManager::~CollisionManager()
{
	Fin();
}

void CollisionManager::Draw()
{
	for (auto aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}

	for (auto sphere : m_Sphere)
	{
		if (sphere)
		{
			sphere->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (m_AABB[i])
		{
			delete m_AABB[i];
			m_AABB[i] = nullptr;
		}
		if (m_Sphere[i])
		{
			delete m_Sphere[i];
			m_Sphere[i] = nullptr;
		}
	}

}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* aabb = nullptr;

	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (!m_AABB[i])
		{
			m_AABB[i] = aabb = new CollisionAABB;
			break;
		}
	}

	return aabb;
}

void CollisionManager::DeleteAABB(CollisionAABB* targetAABB)
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (m_AABB[i] == targetAABB)
		{
			delete targetAABB;
			m_AABB[i] = nullptr;
			break;
		}
	}
}

CollisionSphere* CollisionManager::CreateSphere()
{
	CollisionSphere* sphere = nullptr;

	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (!m_Sphere[i])
		{
			m_Sphere[i] = sphere = new CollisionSphere;
			break;
		}
	}

	return sphere;
}

void CollisionManager::DeleteSphere(CollisionSphere* targetSphere)
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		if (m_Sphere[i] == targetSphere)
		{
			delete targetSphere;
			m_Sphere[i] = nullptr;
			break;
		}
	}
}

void CollisionManager::CheckCollision()
{
	Floor* floor = FloorManager::GetInstance()->GetFloor();

	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* character : characterList)
	{
		CollisionSphere* characterCollision = character->GetSphere();

		MV1_COLL_RESULT_POLY_DIM hitResult = floor->CheckCollisionSphere(characterCollision->GetWorldPos(), characterCollision->GetRadius());
		if (hitResult.HitNum > 0)
		{
			character->HitFloor(floor);
		}

		MV1CollResultPolyDimTerminate(hitResult);
	}

	/*CollisionSphere* playerCollision = player->GetSphere();

	MV1_COLL_RESULT_POLY_DIM playerHitResult = floor->CheckCollisionSphere(playerCollision->GetWorldPos(), playerCollision->GetRadius());
	if (playerHitResult.HitNum > 0)
	{
		player->HitFloor(floor);
	}

	MV1CollResultPolyDimTerminate(playerHitResult);

	CharacterBase* enemy = CharacterManager::GetInstance()->GetCharacter(ENEMY);

	CollisionSphere* enemyCollision = enemy->GetSphere();

	MV1_COLL_RESULT_POLY_DIM enemyHitResult = floor->CheckCollisionSphere(enemyCollision->GetWorldPos(), enemyCollision->GetRadius());
	if (enemyHitResult.HitNum > 0)
	{
		enemy->HitFloor(floor);
	}

	MV1CollResultPolyDimTerminate(enemyHitResult);*/
}
