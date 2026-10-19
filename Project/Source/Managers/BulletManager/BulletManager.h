#pragma once

#include <memory>
#include <vector>
#include "DxLib.h"
#include "../../Component/Bullet/BulletParameter.h"

class GameObject;

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

	std::shared_ptr<GameObject> CreateBullet(BulletType type, VECTOR pos, VECTOR direction);

private:
	static BulletManager* m_Instance;

	std::vector<std::shared_ptr<GameObject>> m_Bullets;
};