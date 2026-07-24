#include "BulletBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../FPS/FPSManager.h"

BulletBase::BulletBase()
{
	m_Pos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_Move = MyMath::VecZero();
	m_Dir = MyMath::VecZero();
	m_Active = false;
	m_IsBoss = false;
	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_Shooter = nullptr;
	m_Handle = 0;
	m_BornTime = 0;
	m_Life = 0;
	m_Damage = 0;
	m_Type = BULLET_TYPE_NONE;
}

BulletBase::~BulletBase()
{
	Fin();
}

void BulletBase::Start()
{
	FPSManager* fpsManager = FPSManager::GetInstance();
	m_BornTime = fpsManager->GetFPS()->GetDeltaTime();

	m_Dir = m_Rot;
}

void BulletBase::Update()
{
	FPSManager* fpsManager = FPSManager::GetInstance();
	int nowTime = fpsManager->GetFPS()->GetDeltaTime();

	if (nowTime - m_BornTime > m_Life)
	{
		m_Active = false;
	}

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void BulletBase::Draw()
{
	if (m_Type == ROBOT_BEAM) return;

	float scale = 1.0f;

	MV1SetScale(m_Handle, VGet(scale, scale, scale));

	MV1SetPosition(m_Handle, m_Pos);

	MV1DrawModel(m_Handle);
}

void BulletBase::Fin()
{
	MV1DeleteModel(m_Handle);

	m_AABB = nullptr;
	m_Sphere = nullptr;
}

void BulletBase::Delete()
{
	m_Active = false;
}