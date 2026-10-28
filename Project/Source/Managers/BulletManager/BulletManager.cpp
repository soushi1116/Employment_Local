#include "BulletManager.h"
#include "../../Component/AllComponents.h"
#include "../../Scene/SceneManager.h"
#include "../../Component/GameObject.h"
#include "../../Collision/CollisionManager.h"
#include <algorithm>
#include <iostream>

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{

}

BulletManager::~BulletManager()
{

}

void BulletManager::Init()
{

}

void BulletManager::Load()
{

}

void BulletManager::Start()
{

}

void BulletManager::Step()
{

}

void BulletManager::Update()
{
	if (!m_NewBullets.empty())
	{
		m_Bullets.insert(m_Bullets.end(), m_NewBullets.begin(), m_NewBullets.end());
		m_NewBullets.clear();
	}

	DeleteBullet();
}

void BulletManager::Draw()
{

}

void BulletManager::Fin()
{

}


std::shared_ptr<GameObject> BulletManager::CreateBullet(BulletType type, VECTOR pos, float dirAngleY, int index)
{
	auto bulletObj = std::make_shared<GameObject>();

	std::shared_ptr<Physics3D> bulletPhysics = bulletObj->AddComponent<Physics3D>();
	std::shared_ptr<Bullet> bullet = bulletObj->AddComponent<Bullet>();
	auto collision = bulletObj->AddComponent<SphereCollision>();
	bulletPhysics->SetCollision(collision);
	bullet->SetType(type);

	bulletPhysics->SetPos(pos);
	bulletPhysics->SetAngleY(dirAngleY);
	bullet->SetPhysics(bulletPhysics);
	bullet->SetSpeed(0.3f);
	bullet->SetLifeLimit(10.0f);

	std::shared_ptr<DamageCollision> damageCollision = bulletObj->AddComponent<DamageCollision>();
	bullet->SetDamageCollision(damageCollision);
	damageCollision->SetActive(true);
	damageCollision->SetPos(pos);
	damageCollision->SetRadius(2.0f);

	CollisionManager::GetInstance()->AddDamageCollision(damageCollision);

	switch (type)
	{
	case BULLET_TYPE_SHURIKEN:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/Shuriken.x");
		bulletObj->SetName("Shuriken");
		damageCollision->SetParentIndex(index);
		damageCollision->SetIsBoss(false);
		damageCollision->SetDamage(20);
		break;
	}
	case BULLET_TYPE_NORMAL_LEAF:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/Leaf.x");
		bulletObj->SetName("Leaf");
		damageCollision->SetParentIndex(index);
		damageCollision->SetIsBoss(false);
		damageCollision->SetDamage(10);
		break;
	}
	case BULLET_TYPE_POISON_LEAF:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/PoisonLeaf.x");
		bulletObj->SetName("PoisonLeaf");
		damageCollision->SetParentIndex(index);
		damageCollision->SetIsBoss(false);
		damageCollision->SetDamage(10);
		break;
	}
	case BULLET_TYPE_MAX:
		break;
	case BULLET_TYPE_NONE:
		break;
	default:
		break;
	}

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();
	nowScene->Instantiate(bulletObj);

	m_NewBullets.push_back(bulletObj);

	return bulletObj;
}

void BulletManager::DeleteBullet()
{
	if (m_Bullets.empty()) return;

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	std::vector<std::shared_ptr<GameObject>> deleteTargets;

	m_Bullets.erase(
		std::remove_if(m_Bullets.begin(), m_Bullets.end(),
			[&deleteTargets](const auto& bullet)
			{
				auto bulletPtr = bullet;

				if (!bulletPtr) return true;

				std::shared_ptr <Bullet> bulletCmp = bulletPtr->GetComponent<Bullet>();

				if (!bulletCmp) return true;

				if (!bulletCmp->IsActive())
				{
					deleteTargets.push_back(bulletPtr);
					return true;
				}

				return false;
			}),
		m_Bullets.end()
	);

	for (const auto& target : deleteTargets)
	{
		nowScene->Delete(target);
	}
}