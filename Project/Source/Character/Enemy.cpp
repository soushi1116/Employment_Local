#include "Enemy.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const VECTOR PLAYER_SIZE = VGet(4.0f, 11.2f, 4.0f);

const float ENEMY_GRAVITY = 0.01f;

Enemy::Enemy() : CharacterBase()
{

}

Enemy::~Enemy()
{
	Fin();
}

void Enemy::Init()
{

}

void Enemy::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Enemy::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;

	m_Type = PLAYER;

	m_Pos = VGet(0.0f, 0.0f, 5.0f);
	m_Rot = VGet(0.0f, DX_PI_F, 0.0f);

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.7f, 0.0f));
	m_AABB->SetSize(PLAYER_SIZE);
}

void Enemy::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Move.y = m_Gravity;

	if (!m_Randing) m_Gravity -= ENEMY_GRAVITY;
}

void Enemy::Damage()
{
	m_Pos.z += 1.0f;
}