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

	Physics3D* bulletPhysics = bulletObj->AddComponent<Physics3D>().get();
	Bullet* bullet = bulletObj->AddComponent<Bullet>().get();
	auto collision = bulletObj->AddComponent<SphereCollision>().get();
	bulletPhysics->SetCollision(collision);
	bullet->SetType(type);

	bulletPhysics->SetPos(pos);
	bulletPhysics->SetAngleY(dirAngleY);
	bullet->SetPhysics(bulletPhysics);
	bullet->SetSpeed(0.3f);
	bullet->SetLifeLimit(10.0f);

	DamageCollision* damageCollision = bulletObj->AddComponent<DamageCollision>().get();
	bullet->SetDamageCollision(damageCollision);
	damageCollision->SetActive(true);
	damageCollision->SetRadius(2.0f);

	CollisionManager::GetInstance()->AddDamageCollision(damageCollision);

	switch (type)
	{
	case BULLET_TYPE_SHURIKEN:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/Shuriken.x");
		bulletObj->SetName("Shuriken");
		damageCollision->SetParentIndex(index);
		damageCollision->SetDamage(20);
		break;
	}
	case BULLET_TYPE_NORMAL_LEAF:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/Leaf.x");
		break;
	}
	case BULLET_TYPE_POISON_LEAF:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/PoisonLeaf.x");
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

	m_Bullets.erase(
		std::remove_if(m_Bullets.begin(), m_Bullets.end(),
			[nowScene](const auto& bullet)
			{
				auto bulletPtr = bullet.lock();

				if (!bulletPtr) return true;

				std::shared_ptr <Bullet> bulletCmp = bulletPtr->GetComponent<Bullet>();

				if (!bulletCmp) return true;

				if (!bulletCmp->IsActive())
				{
					nowScene->Delete(bulletPtr);
					return true;
				}

				return false;
			}),
		m_Bullets.end()
	);
}