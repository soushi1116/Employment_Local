#include "ItemBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"

const int RESPAWN_INTERVAL = 180;

ItemBase::ItemBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_Handle = 0;
	m_Type = ITEM_TYPE_NONE;
}

ItemBase::~ItemBase()
{
	Fin();
}

void ItemBase::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void ItemBase::Draw()
{
	float scale = 0.02f;

	MV1SetScale(m_Handle, VGet(scale, scale, scale));

	MV1SetPosition(m_Handle, m_Pos);

	MV1DrawModel(m_Handle);
}

void ItemBase::Fin()
{
	MV1DeleteModel(m_Handle);
}