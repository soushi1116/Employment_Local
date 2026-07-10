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
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerEffect.h"

const float PLAYER_ROTATION_SPEED = 0.03f;
const float PLAYER_MOVE_SPEED = 0.3f;

const float PLAYER_SUPER_ATTACK_MOVE_SPEED = 0.3f;

const VECTOR PLAYER_SIZE = VGet(0.6f, 1.70f, 0.6f);

const VECTOR SWORD_POS_OFFSET = VGet(2.0f, 3.0f, 4.0f);
const VECTOR SWORD_COLLISION_SIZE = VGet(1.0f, 10.0f, 6.0f);

const int PLAYER_DEFAULT_POWER = 10;
const int PLAYER_SKILL_POINT_SPEND = 10;
const int PLAYER_SUPER_ATTACK_POINT_SPEND = 10;

Player::Player() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 110.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 33.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 45.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 71.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 73.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 180.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 30.0f;
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
	m_Handle = MV1LoadModel("Data/Character/Knight.x");

	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
	}	
}

void Player::Start()
{
	CharacterBase::Start();

	m_SkillPointSpend = PLAYER_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = PLAYER_SUPER_ATTACK_POINT_SPEND;

	m_Active = true;

	m_Radius = PLAYER_SIZE.y * m_Scale.y / 2.0f;

	m_Speed = PLAYER_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = PLAYER_DEFAULT_POWER;

	m_SuperAttackPoint = 30;

	m_NowAnimation = ANIMATION_STOP;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, PLAYER_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(PLAYER_SIZE.x * m_Scale.x, PLAYER_SIZE.y * m_Scale.y, PLAYER_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, PLAYER_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(m_Radius);

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

void Player::Attack()
{
	CharacterBase::Attack();
}

void Player::Skill()
{
	if (m_SkillPoint > 10)
	{
		CharacterBase::Skill();

		m_Power++;
	}
}

void Player::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();

		EffekseerEffect* effect = EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_KNIGHT_SUPER_ATTACK, m_Pos);
		effect->SetParentCharacter(this);
	}
}

