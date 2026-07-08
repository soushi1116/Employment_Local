#pragma once
#include "BulletBase.h"
#include <list>

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new BulletManager;
		}
	}

	static BulletManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void CreateBullet(BulletType type, VECTOR pos, VECTOR rot);
	void DeleteBullet();
	std::list<BulletBase*> GetBulletList() { return m_BulletList; }

private:
	static BulletManager* m_Instance;

	BulletBase* m_Bullet[BULLET_TYPE_MAX];

	std::list<BulletBase*> m_BulletList;


};

