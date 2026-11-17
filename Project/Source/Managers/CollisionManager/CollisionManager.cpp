#include "CollisionManager.h"
#include "../CharacterManager/CharacterManager.h"
#include "../MapManager/MapManager.h"
#include "../ItemManager/ItemManager.h"
#include "../BulletManager/BulletManager.h"
#include "../CameraManager/CameraManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Component/AllComponents.h"

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

	CheckCharacterItem();
}

void CollisionManager::CheckCharacterStage()
{
	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	std::shared_ptr<GameObject> stage = nowScene->GetOneGameObjectByTag(TAG_STAGE);
	std::vector<std::shared_ptr<GameObject>> characters = nowScene->GetGameObjectsByTag(TAG_CHARACTER);

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

	std::vector<std::shared_ptr<GameObject>> characters = nowScene->GetGameObjectsByTag(TAG_CHARACTER);

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

	std::vector<std::shared_ptr<GameObject>> characters = nowScene->GetGameObjectsByTag(TAG_CHARACTER);

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

void CollisionManager::CheckCharacterItem()
{
	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	std::vector<std::shared_ptr<GameObject>> characters = nowScene->GetGameObjectsByTag(TAG_CHARACTER);
	std::vector<std::shared_ptr<GameObject>> items = nowScene->GetGameObjectsByTag(TAG_ITEM);

	for (auto& character : characters)
	{
		for (auto& item : items)
		{
			character->GetComponent<CharacterMove>()->CollisionItem(item);
		}
	}
}