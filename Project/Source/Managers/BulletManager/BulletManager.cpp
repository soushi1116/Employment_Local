#include "BulletManager.h"
#include "../../Component/AllComponents.h"
#include "../../Scene/SceneManager.h"
#include "../../Component/GameObject.h"

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

}

void BulletManager::Draw()
{

}

void BulletManager::Fin()
{

}


std::shared_ptr<GameObject> BulletManager::CreateBullet(BulletType type, VECTOR pos, VECTOR direction)
{
	auto bulletObj = std::make_shared<GameObject>();

	std::shared_ptr<Physics3D> bulletPhysics = bulletObj->AddComponent<Physics3D>();
	std::shared_ptr<BulletParameter> bulletParam = bulletObj->AddComponent<BulletParameter>();
	auto collision = std::make_shared<SphereCollision>();
	bulletPhysics->SetCollision(collision);
	bulletParam->SetType(type);

	bulletPhysics->SetPos(pos);
	bulletParam->SetPhysics(bulletPhysics);
	bulletParam->SetSpeed(1.0f);

	switch (type)
	{
	case BULLET_TYPE_SHURIKEN:
	{
		auto model = bulletObj->AddComponent<ModelRenderer>("Data/Bullet/Shuriken.x");
		bulletObj->SetName("Shuriken");
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

	return bulletObj;
}
