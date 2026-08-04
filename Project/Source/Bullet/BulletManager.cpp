#include "BulletManager.h"
#include "BotBeam.h"
#include "Shuriken.h"
#include "BeastJumpWave.h"
#include "NormalLeaf.h"
#include "PoisonLeaf.h"
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
	int i = 1;

	for (auto& bullet : m_BulletList)
	{
		bullet->Draw();

		DrawFormatString(0, 50 * i, GetColor(255, 255, 255), "Scale:%f", bullet->GetRadius());

		i++;
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
	case ROBOT_BEAM:
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
	case SHURIKEN:
	{
		Shuriken* shuriken = new Shuriken;

		shuriken->SetPos(pos);
		shuriken->SetRot(rot);

		shuriken->Init();
		shuriken->Load();
		shuriken->Start();

		m_BulletList.push_back(shuriken);

		return shuriken;
	}
	break;
	case BEAST_JUMP_WAVE:
	{
		BeastJumpWave* beastJumpWave = new BeastJumpWave;

		beastJumpWave->Init();

		beastJumpWave->SetPos(pos);
		beastJumpWave->SetRot(rot);

		beastJumpWave->Load();
		beastJumpWave->Start();

		m_BulletList.push_back(beastJumpWave);

		return beastJumpWave;
	}
	case NORMAL_LEAF:
	{
		NormalLeaf* normalLeaf = new NormalLeaf;

		normalLeaf->Init();

		normalLeaf->SetPos(pos);
		normalLeaf->SetRot(rot);

		normalLeaf->Load();
		normalLeaf->Start();

		m_BulletList.push_back(normalLeaf);

		return normalLeaf;
	}
	case POISON_LEAF:
	{
		PoisonLeaf* poisonLeaf = new PoisonLeaf;

		poisonLeaf->Init();

		poisonLeaf->SetPos(pos);
		poisonLeaf->SetRot(rot);

		poisonLeaf->Load();
		poisonLeaf->Start();

		m_BulletList.push_back(poisonLeaf);

		return poisonLeaf;
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

