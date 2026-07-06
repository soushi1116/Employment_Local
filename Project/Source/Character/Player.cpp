#include "Player.h"
#include <math.h>
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Camera/CameraManager.h"
#include "../Camera/CameraBase.h"

const float PLAYER_ROTATION_SPEED = 0.03f;
const float PLAYER_MOVE_SPEED = 0.3f;

const float PLAYER_SUPER_ATTACK_MOVE_SPEED = 0.5f;

const VECTOR PLAYER_SIZE = VGet(4.0f, 11.2f, 4.0f);

const VECTOR SWORD_POS_OFFSET = VGet(2.0f, 3.0f, 4.0f);
const VECTOR SWORD_COLLISION_SIZE = VGet(1.0f, 10.0f, 6.0f);

const int PLAYER_DEFAULT_POWER = 10;

Player::Player() : CharacterBase()
{
	
}

Player::~Player()
{
	Fin();
}

void Player::Init()
{
	m_Type = PLAYER;
	CharacterBase::Init();
}

void Player::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Player::Start()
{
	CharacterBase::Start();

	m_Active = true;

	m_Speed = PLAYER_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = PLAYER_DEFAULT_POWER;

	m_SuperAttackPoint = 30;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(PLAYER_SIZE.x * m_Scale.x, PLAYER_SIZE.y * m_Scale.y, PLAYER_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(PLAYER_SIZE.y  * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Player::Step()
{
	CharacterBase::Step();

	if (!m_Dead)
	{
		if (m_ActionType == ACTION_SUPER_ATTACK)
		{
			m_Move.x = PLAYER_SUPER_ATTACK_MOVE_SPEED * sinf(m_Rot.y);
			m_Move.z = PLAYER_SUPER_ATTACK_MOVE_SPEED * cosf(m_Rot.y);
		}
	}
}

