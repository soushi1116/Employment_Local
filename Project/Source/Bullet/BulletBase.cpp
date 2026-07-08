#include "BulletBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"

const int RESPAWN_INTERVAL = 180;

BulletBase::BulletBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_Handle = 0;
	m_Type = BULLET_TYPE_NONE;
}

BulletBase::~BulletBase()
{
	Fin();
}

void BulletBase::Update()
{
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void BulletBase::Draw()
{
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