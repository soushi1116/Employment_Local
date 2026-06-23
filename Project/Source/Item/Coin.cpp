#include "Coin.h"
#include "ItemParameter.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"

const VECTOR COIN_SIZE = VGet(4.0f, 4.0f, 1.0f);

Coin::Coin() : ItemBase()
{
	
}

Coin::~Coin()
{
	Fin();
}

void Coin::Init()
{
	m_Type = COIN;
}

void Coin::Load()
{
	m_Handle = MV1LoadModel("Data/Item/Coin.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Coin::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Pos.y = -8.0f;

	m_Active = true;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	VECTOR aabbSize = VGet(COIN_SIZE.x * m_Scale.x, COIN_SIZE.y * m_Scale.y, COIN_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Sphere->SetRadius(COIN_SIZE.y * m_Scale.y / 2.0f);
}

void Coin::Step()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);

	MV1RefreshCollInfo(m_Handle);
}

