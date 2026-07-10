#include "BulletManager.h"
#include "BotBeam.h"
#include "../MyMath/MyMath.h"

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{
	for (int i = 0; i < BULLET_TYPE_MAX; i++)
	{
		m_Bullet[i] = nullptr;
	}

}

BulletManager::~BulletManager()
{
	Fin();
}

void BulletManager::Init()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Init();
	}
}

void BulletManager::Load()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Load();
	}
}

void BulletManager::Start()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Start();
	}
}

void BulletManager::Step()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Step();
	}
}

void BulletManager::Update()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Update();
	}

	DeleteBullet();
}

void BulletManager::Draw()
{
	for (auto& bullet : m_BulletList)
	{
		bullet->Draw();
	}

	SetUseLighting(TRUE);
}

void BulletManager::Fin()
{
	for (auto& bullet : m_BulletList)
	{
		delete bullet;
	}

	m_BulletList.clear();

	for (auto bullet : m_Bullet)
	{
		delete bullet;
	}
}

BulletBase* BulletManager::CreateBullet(BulletType type, VECTOR pos, VECTOR rot)
{

	BulletBase* bullet = nullptr;

	switch (type)
	{
	case BOT_BEAM:
	{
		BotBeam* bullet = new BotBeam;

		bullet->SetPos(pos);
		bullet->SetRot(rot);

		bullet->Init();
		bullet->Load();
		bullet->Start();

		m_BulletList.push_back(bullet);

		return bullet;
	}
	break;
	case BULLET_TYPE_MAX:
		break;
	case BULLET_TYPE_NONE:
		break;
	default:
		break;
	}
}

void BulletManager::DeleteBullet()
{
	m_BulletList.remove_if([](const BulletBase* bullet) {
		if (!bullet) return true;

		if (!bullet->IsActive())
		{
			delete bullet;
			return true;
		}
		return false;
		});

}

