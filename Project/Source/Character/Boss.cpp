#include "Boss.h"
#include <math.h>
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Camera/CameraManager.h"
#include "../Camera/CameraBase.h"
#include "../Bullet/BulletManager.h"

const float PLAYER_ROTATION_SPEED = 0.03f;
const float PLAYER_MOVE_SPEED = 0.3f;

const float PLAYER_SUPER_ATTACK_MOVE_SPEED = 0.5f;

const float BOSS_SIZE_OFFSET = 1.3f;

const VECTOR BOSS_SIZE = VGet(0.6f, 1.8f, 0.6f);

const VECTOR SWORD_POS_OFFSET = VGet(2.0f, 3.0f, 4.0f);
const VECTOR SWORD_COLLISION_SIZE = VGet(1.0f, 10.0f, 6.0f);

const int PLAYER_DEFAULT_POWER = 10;

Boss::Boss() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 250.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 33.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 70.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 71.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 129.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 117.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 21.0f;
}

Boss::~Boss()
{
	Fin();
}

void Boss::Init()
{
	m_Type = PLAYER;
	CharacterBase::Init();
}

void Boss::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Bot.x");

	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
	}
}

void Boss::Start()
{
	CharacterBase::Start();

	m_Radius = BOSS_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, BOSS_SIZE_OFFSET);

	m_Active = true;

	m_Speed = PLAYER_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = PLAYER_DEFAULT_POWER;

	m_SuperAttackPoint = 30;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, BOSS_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(BOSS_SIZE.x * m_Scale.x, BOSS_SIZE.y * m_Scale.y, BOSS_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, BOSS_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(BOSS_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Boss::Step()
{
	CharacterBase::Step();

	if (!m_Dead)
	{
		
	}
}

void Boss::Attack()
{
	CharacterBase::Attack();
}

void Boss::Skill()
{
	if (m_SkillPoint > 10)
	{
		CharacterBase::Skill();
		
		m_Hp += 300;

		if (m_Hp > m_MaxHp)
		{
			m_Hp = m_MaxHp;
		}
	}
}

void Boss::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();

		VECTOR beamPos = VGet(m_Pos.x, m_Pos.y + 20.0f, m_Pos.z);

		BulletManager::GetInstance()->CreateBullet(BOT_BEAM, beamPos, m_Rot);
	}
}

