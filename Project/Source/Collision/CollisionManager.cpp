#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/MapManager/MapManager.h"
#include "../Item/ItemManager.h"
#include "../Managers/BulletManager/BulletManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../Scene/SceneManager.h"
#include "../Component/AllComponents.h"

CollisionManager* CollisionManager::m_Instance = nullptr;

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	
}

void CollisionManager::CheckCollision()
{
	CheckCharacterStage();

	CheckCharacterCharacter();

	CheckCharacterDamage();
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

	int stageCollisionHandle = stage->GetComponent<Physics3D>()->GetCollision<MeshCollision>()->GetCollisionHandle();

	for (auto& character : characters)
	{
		character->GetComponent<CharacterMove>()->CollisionStage(stageCollisionHandle);
	}
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

			std::shared_ptr<Physics3D> targetPhysics = targetCharacter->GetComponent<Physics3D>();

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

			if (character->GetComponent<CharacterParameter>()->IsBoss() == damageCollision->IsBoss()) continue;

			if (damageCollision->AlreadyHit(character->GetComponent<CharacterParameter>()->GetIndex())) continue;

			character->GetComponent<CharacterMove>()->CollisionDamage(damageCollision);
		}
	}
}

