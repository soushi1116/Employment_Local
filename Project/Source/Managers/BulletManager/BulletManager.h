#pragma once

#include <memory>
#include <vector>
#include "DxLib.h"
#include "../../Component/Bullet/Bullet.h"
#include "../Singleton.h"

class GameObject;

class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	~BulletManager();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	std::shared_ptr<GameObject> CreateBullet(BulletType type, VECTOR pos, float dirAngleY, int index, int damage);
	void DeleteBullet();

private:
	static BulletManager* m_Instance;

	std::vector<std::weak_ptr<GameObject>> m_Bullets;
	std::vector<std::shared_ptr<GameObject>> m_NewBullets;
};