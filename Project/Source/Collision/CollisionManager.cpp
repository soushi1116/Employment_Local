#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Character/CharacterManager.h"
#include "../Map/MapManager.h"
#include "../Item/ItemManager.h"
#include "../Bullet/BulletManager.h"
#include "../Camera/CameraManager.h"
#include "../Scene/SceneManager.h"
#include "../Component/AllComponents.h"

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
#ifdef _DEBUG
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
#endif	
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

//void CollisionManager::SetUpCollision(std::shared_ptr<_3DPhysics> physics, CollisionType type)
//{
//	CollisionBase* collision = nullptr;
//
//	switch (type)
//	{
//	case BOX_COLLISION:
//		collision = new BoxCollision(physics->GetOwner());
//		break;
//	case SPHERE_COLLISION:
//		collision = new SphereCollision(physics->GetOwner());
//		break;
//	case MESH_COLLISION:
//		collision = new MeshCollision(physics->GetOwner());
//		break;
//	case COLLISION_TYPE_MAX:
//		break;
//	case COLLISION_TYPE_NONE:
//		break;
//	default:
//		break;
//	}
//
//	physics->SetCollision(collision);
//}

void CollisionManager::CheckCollision()
{
	CheckCharacterStage();

	CheckCharacterCharacter();

	CheckCharacterDamage();
	
	CheckCharacterAttack();

	CheckCharacterSuperAttack();

	CheckCharacterBullet();

	CheckCameraStage();

	CheckRooterStage();

	CheckBulletStage();
}

void CollisionManager::CheckCharacterStage()
{
	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	auto gameObjects = nowScene->GetGameObjects();

	std::shared_ptr<GameObject> stage;
	std::vector<std::shared_ptr<GameObject>> characters;

	for (auto& obj : gameObjects)
	{
		if (obj->CompareTag(TAG_STAGE))
		{
			stage = obj;
		}
		else if (obj->CompareTag(TAG_CHARACTER))
		{
			characters.push_back(obj);
		}
	}

	if (stage == nullptr) return;

	int stageCollisionHandle = stage->GetComponent<_3DPhysics>()->GetCollision<MeshCollision>()->GetCollisionHandle();

	for (auto& character : characters)
	{
		character->GetComponent<CharacterMove>()->CollisionStage(stageCollisionHandle);
	}
}

void CollisionManager::CheckCharacterBullet()
{
	/*const auto& bulletList = BulletManager::GetInstance()->GetBulletList();

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
	}*/
}

void CollisionManager::CheckCharacterCharacter()
{
	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	auto gameObjects = nowScene->GetGameObjects();

	std::vector<std::shared_ptr<GameObject>> characters;

	for (auto& obj : gameObjects)
	{
		if (obj->CompareTag(TAG_CHARACTER))
		{
			characters.push_back(obj);
		}
	}

	for (auto& thisCharacter : characters)
	{
		std::shared_ptr<CharacterParameter> thisParam = thisCharacter->GetComponent<CharacterParameter>();
		if (thisParam->IsBoss()) continue;

		for (auto& targetCharacter : characters)
		{
			if (thisCharacter == targetCharacter) continue;

			std::shared_ptr<_3DPhysics> targetPhysics = targetCharacter->GetComponent<_3DPhysics>();

			thisCharacter->GetComponent<CharacterMove>()->CollisionCharacter(targetPhysics);
		}
	}
}

void CollisionManager::CheckCharacterDamage()
{
	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	auto gameObjects = nowScene->GetGameObjects();

	std::vector<std::shared_ptr<GameObject>> characters;

	for (auto& obj : gameObjects)
	{
		if (obj->CompareTag(TAG_CHARACTER))
		{
			characters.push_back(obj);
		}
	}

	for (auto& character : characters)
	{
		for (auto& damageCollision : m_DamageCollisions)
		{
			if (!damageCollision->IsActive()) continue;

			if (character->GetComponent<CharacterParameter>()->GetIndex() == damageCollision->GetParentIndex()) continue;

			if (damageCollision->AlreadyHit(character->GetComponent<CharacterParameter>()->GetIndex())) continue;

			character->GetComponent<CharacterMove>()->CollisionDamage(damageCollision);
		}
	}
}

void CollisionManager::CheckCharacterAttack() 
{
	/*const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* attacker : characterList) {
		if (attacker->GetActionType() != ACTION_ATTACK) continue;

		CollisionSphere* attackerCollision = attacker->GetSphere();
		if (!attackerCollision) continue;

		for (CharacterBase* victim : characterList) 
		{
			if (attacker->GetIndex() == victim->GetIndex()) continue;

			if (attacker->IsAlreadyHit(victim->GetIndex())) continue;

			MV1_COLL_RESULT_POLY_DIM hitResult = victim->CheckCollisionSphere(
				attackerCollision->GetWorldPos(),
				attackerCollision->GetRadius()
			);

			if (hitResult.HitNum > 0) 
			{
				if (attacker->IsBoss() != victim->IsBoss())
				{
					victim->Damage(attacker, (int)((float)attacker->GetPower() * attacker->GetPowerMagni() / victim->GetDefenceMagni()));

					attacker->AddHitVictim(victim->GetIndex());

					MV1CollResultPolyDimTerminate(hitResult);
					break;
				}
			}

			MV1CollResultPolyDimTerminate(hitResult);
		}
	}*/
}

void CollisionManager::CheckCharacterSuperAttack()
{
	/*const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (CharacterBase* attacker : characterList) {
		if (attacker->GetActionType() != ACTION_SUPER_ATTACK) continue;

		CharacterType attackerType = attacker->GetType();

		if (attackerType != KNIGHT) continue;

		CollisionSphere* attackerCollision = attacker->GetSphere();
		if (!attackerCollision) continue;

		for (CharacterBase* victim : characterList)
		{
			if (attacker->GetIndex() == victim->GetIndex()) continue;

			if (attacker->IsAlreadyHit(victim->GetIndex())) continue;

			MV1_COLL_RESULT_POLY_DIM hitResult = victim->CheckCollisionSphere(
				attackerCollision->GetWorldPos(),
				attackerCollision->GetRadius()
			);

			if (hitResult.HitNum > 0)
			{
				if (attacker->IsBoss() != victim->IsBoss())
				{
					victim->Damage(attacker, (int)((float)attacker->GetPower() * attacker->GetPowerMagni() / victim->GetDefenceMagni()));

					attacker->AddHitVictim(victim->GetIndex());

					MV1CollResultPolyDimTerminate(hitResult);
					break;
				}
			}

			MV1CollResultPolyDimTerminate(hitResult);
		}
	}*/
}

void CollisionManager::CheckCameraStage()
{
	//static int frameCount = 0;
	//if (frameCount < 5)
	//{
	//	frameCount++;
	//	return;
	//}

	//MapBase* map = MapManager::GetInstance()->GetCurrentMap();
	////CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
	//CameraBase* camera = CameraManager::GetInstance()->GetCamera(DEBUG_CAMERA);

	//CollisionSphere* cameraCollision = camera->GetSphere();

	//MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(cameraCollision->GetWorldPos(), cameraCollision->GetRadius());
	//if (hitResult.HitNum > 0)
	//{
	//	camera->HitStage(&hitResult);
	//}

	//MV1CollResultPolyDimTerminate(hitResult);
}

void CollisionManager::CheckRooterStage()
{
	/*MapBase* map = MapManager::GetInstance()->GetCurrentMap();

	const auto& rooterList = CharacterManager::GetInstance()->GetRooterList();

	for (Rooter* rooter : rooterList)
	{
		CollisionSphere* rooterCollision = rooter->GetSphere();

		MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(rooterCollision->GetWorldPos(), rooterCollision->GetRadius());
		if (hitResult.HitNum > 0)
		{
			rooter->HitStage(map);
		}

		MV1CollResultPolyDimTerminate(hitResult);
	}*/
}

void CollisionManager::CheckBulletStage()
{
	/*MapBase* map = MapManager::GetInstance()->GetCurrentMap();

	const auto& bulletList = BulletManager::GetInstance()->GetBulletList();

	for (BulletBase* bullet : bulletList)
	{
		CollisionSphere* characterCollision = bullet->GetSphere();

		MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(characterCollision->GetWorldPos(), characterCollision->GetRadius());
		if (hitResult.HitNum > 0)
		{
			bullet->HitStage();
		}

		MV1CollResultPolyDimTerminate(hitResult);
	}*/
}
