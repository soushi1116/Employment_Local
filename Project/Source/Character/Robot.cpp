#include "Robot.h"
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

const float ROBOT_ROTATION_SPEED = 0.03f;
const float ROBOT_MOVE_SPEED = 1.0f;

const float ROBOT_SIZE_OFFSET = 1.3f;

const VECTOR ROBOT_SIZE = VGet(0.6f, 1.8f, 0.6f);

const int ROBOT_DEFAULT_POWER = 10;
const int ROBOT_SKILL_POINT_SPEND = 10;
const int ROBOT_SUPER_ATTACK_POINT_SPEND = 10;
const int ROBOT_SKILL_HP_HEAL = 100;

Robot::Robot() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 250.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 33.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 71.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 129.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 117.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 21.0f;
	m_AnimTotalTimes[ANIMATION_RUN] = 19.0f;
}

Robot::~Robot()
{
	Fin();
}

void Robot::Init()
{
	m_Type = ROBOT;
	CharacterBase::Init();
}

void Robot::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Robot.x");

	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
	}
}

void Robot::Start()
{
	CharacterBase::Start();

	m_Radius = ROBOT_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, ROBOT_SIZE_OFFSET);

	m_Active = true;

	m_Speed = ROBOT_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = ROBOT_DEFAULT_POWER;

	m_SuperAttackPoint = 30;
	m_SkillPointSpend = ROBOT_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = ROBOT_SUPER_ATTACK_POINT_SPEND;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, ROBOT_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(ROBOT_SIZE.x * m_Scale.x, ROBOT_SIZE.y * m_Scale.y, ROBOT_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, ROBOT_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(ROBOT_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Robot::Step()
{
	CharacterBase::Step();
}

void Robot::Attack()
{
	CharacterBase::Attack();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_ROBOT_ATTACK);
}

void Robot::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_ROBOT_SKILL);

		m_Hp += ROBOT_SKILL_HP_HEAL;

		if (m_Hp > m_MaxHp)
		{
			m_Hp = m_MaxHp;
		}
	}
}

void Robot::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_ROBOT_SUPER_ATTACK);

		VECTOR beamPos = VGet(m_Pos.x, m_Pos.y + 10.0f, m_Pos.z);

		BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(ROBOT_BEAM, beamPos, m_Rot);

		bullet->SetShooter(this);
	}
}

