#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Character/CharacterManager.h"
#include "../Floor/FloorManager.h"
#include "../Item/ItemManager.h"
#include "../Bullet/BulletManager.h"

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
			//aabb->Draw();
		}
	}

	for (auto sphere : m_Sphere)
	{
		if (sphere)
		{
			//sphere->Draw();
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
	CheckCharacterStage();
	CheckCharacterBullet();
}

void CollisionManager::CheckCharacterStage()
{
	Floor* floor = FloorManager::GetInstance()->GetFloor();

	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* character : characterList)
	{
		CollisionSphere* characterCollision = character->GetSphere();

		MV1_COLL_RESULT_POLY_DIM hitResult = floor->CheckCollisionSphere(characterCollision->GetWorldPos(), characterCollision->GetRadius());
		if (hitResult.HitNum > 0)
		{
			character->HitStage(floor);
		}

		MV1CollResultPolyDimTerminate(hitResult);
	}
}

void CollisionManager::CheckCharacterBullet()
{
	const auto& bulletList = BulletManager::GetInstance()->GetBulletList();

	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* character : characterList)
	{
		for (BulletBase* bullet : bulletList)
		{
			CollisionAABB* characterCollision = character->GetAABB();
			CollisionAABB* bulletCollision = bullet->GetAABB();

			const HitResultAABB hitResult = characterCollision->CheckAABB(bulletCollision);
			
			if (hitResult.m_IsHit)
			{
				character->HitBullet(bullet);
			}
		}
	}
}

void CollisionManager::CheckCharacterCharacter()
{
	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* thisCharacter : characterList)
	{
		for (CharacterBase* opponent : characterList)
		{
			if (thisCharacter == opponent) continue;

			CollisionAABB* thisCollision = thisCharacter->GetAABB();
			CollisionAABB* opponentCollision = opponent->GetAABB();

			const HitResultAABB hitResult = thisCollision->CheckAABB(opponentCollision);

			if (hitResult.m_IsHit)
			{
				thisCharacter->HitCharacter(opponent);
			}
		}
	}
}
