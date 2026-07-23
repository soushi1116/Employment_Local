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
#include "../Sound/SoundManager.h"

const float BOT_ROTATION_SPEED = 0.03f;
const float BOT_MOVE_SPEED = 0.8f;

const float BOT_SIZE_OFFSET = 1.3f;

const VECTOR BOT_SIZE = VGet(0.6f, 1.8f, 0.6f);

const int BOT_DEFAULT_POWER = 10;
const int BOT_SKILL_POINT_SPEND = 10;
const int BOT_SUPER_ATTACK_POINT_SPEND = 10;
const int BOT_SKILL_HP_HEAL = 100;

Boss::Boss() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 250.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 33.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
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
	m_Type = ROBOT;
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

	m_Radius = BOT_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, BOT_SIZE_OFFSET);

	m_Active = true;

	m_Speed = BOT_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = BOT_DEFAULT_POWER;

	m_SuperAttackPoint = 30;
	m_SkillPointSpend = BOT_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = BOT_SUPER_ATTACK_POINT_SPEND;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, BOT_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(BOT_SIZE.x * m_Scale.x, BOT_SIZE.y * m_Scale.y, BOT_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, BOT_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(BOT_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Boss::Step()
{
	CharacterBase::Step();
}

void Boss::Attack()
{
	CharacterBase::Attack();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_BOT_ATTACK);
}

void Boss::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_ROBOT_SKILL);
		
		m_Hp += BOT_SKILL_HP_HEAL;

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

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_ROBOT_SUPER_ATTACK);

		VECTOR beamPos = VGet(m_Pos.x, m_Pos.y + 10.0f, m_Pos.z);

		BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(BOT_BEAM, beamPos, m_Rot);

		bullet->SetShooter(this);
	}
}

