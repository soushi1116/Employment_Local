#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Character/CharacterManager.h"
#include "../Map/MapManager.h"
#include "../Item/ItemManager.h"
#include "../Bullet/BulletManager.h"
#include "../Camera/CameraManager.h"
#include "../Scene/SceneManager.h"

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
	CheckCharacterStage();
	
	SceneType nowScene = SceneManager::GetInstance()->GetNowScene();

	CheckCharacterCharacter();

	CheckCharacterAttack();

	CheckCharacterBullet();

	CheckCameraStage();
}

void CollisionManager::CheckCharacterStage()
{
	Map* map = MapManager::GetInstance()->GetMap();

	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* character : characterList)
	{
		CollisionSphere* characterCollision = character->GetSphere();

		MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(characterCollision->GetWorldPos(), characterCollision->GetRadius());
		if (hitResult.HitNum > 0)
		{
			character->HitStage(map);
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
		CollisionSphere* characterCollision = character->GetSphere();

		for (BulletBase* bullet : bulletList)
		{
			if (character->IsBoss() == bullet->IsBoss()) continue;

			CollisionSphere* bulletCollision = bullet->GetSphere();

			float difX = characterCollision->GetWorldPos().x - bulletCollision->GetWorldPos().x;
			float difY = characterCollision->GetWorldPos().y - bulletCollision->GetWorldPos().y;
			float difZ = characterCollision->GetWorldPos().z - bulletCollision->GetWorldPos().z;

			float difSquare = difX * difX + difY * difY + difZ * difZ;

			float radiusSum = characterCollision->GetRadius() + bulletCollision->GetRadius();
			float radiusSumSquare = radiusSum * radiusSum;
			
			if (difSquare <= radiusSumSquare)
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

void CollisionManager::CheckCharacterAttack()
{
	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* character : characterList)
	{
		CollisionSphere* characterCollision = character->GetSphere();

		for (CharacterBase* opponent : characterList)
		{
			if (character->GetIndex() == opponent->GetIndex()) continue;

			MV1_COLL_RESULT_POLY_DIM hitResult = opponent->CheckCollisionSphere(characterCollision->GetWorldPos(), characterCollision->GetRadius());
			if (hitResult.HitNum > 0)
			{
				if (character->GetAttackHitFlag())
				{
					opponent->Damage(character, character->GetPower());
					character->AttackHitFlagFalse();
				}
			}

			MV1CollResultPolyDimTerminate(hitResult);
		}
	}
}

void CollisionManager::CheckCameraStage()
{
	static int frameCount = 0;
	if (frameCount < 5)
	{
		frameCount++;
		return;
	}

	Map* map = MapManager::GetInstance()->GetMap();
	CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);

	CollisionSphere* cameraCollision = camera->GetSphere();

	MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(cameraCollision->GetWorldPos(), cameraCollision->GetRadius());
	if (hitResult.HitNum > 0)
	{
		camera->HitStage(&hitResult);
	}

	MV1CollResultPolyDimTerminate(hitResult);
}
