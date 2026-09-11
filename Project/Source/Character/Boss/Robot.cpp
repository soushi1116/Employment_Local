#include "Robot.h"
#include <math.h>
#include "../CharacterParameter.h"
#include "../../Input/Input.h"
#include "../../MyMath/MyMath.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"
#include "../../Collision/CollisionSphere.h"
#include "../../Camera/CameraManager.h"
#include "../../Camera/CameraBase.h"
#include "../../Bullet/BulletManager.h"
#include "../../Sound/SoundManager.h"

const float ROBOT_ROTATION_SPEED = 0.03f;
const float ROBOT_MOVE_SPEED = 1.0f;

const float ROBOT_SIZE_OFFSET = 1.3f;

const float ROBOT_ATTACK_RANGE = 10.0f;
const float ROBOT_SUPER_ATTACK_RANGE = 100.0f;

const float ATTACK_SE_OFFSET = 40.0f; // ’ÊíUŒ‚‚ÌSEƒ^ƒCƒ~ƒ“ƒO•â³
const float SUPER_ATTACK_SE_OFFSET = 30.0f; // •KŽE‹Z‚Ì”­ŽËASEƒ^ƒCƒ~ƒ“ƒO•â³
const float SUPER_ATTACK_POS_OFFSET_FORWARD = 15.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‘O•û•â³
const float SUPER_ATTACK_POS_OFFSET_HEIGHT = 20.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‚‚³•â³

const VECTOR ROBOT_SIZE = VGet(0.6f, 1.8f, 0.6f);

const int ROBOT_DEFAULT_POWER = 10;
const int ROBOT_SKILL_POINT_SPEND = 10;
const int ROBOT_SUPER_ATTACK_POINT_SPEND = 10;
const int ROBOT_SKILL_HP_HEAL = 100;
const int ROBOT_MAX_HP = 300;

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
	CharacterBase::Load();

	m_Handle = MV1LoadModel("Data/Character/Robot.x");

	m_IconHandle = LoadGraph("Data/UI/Character/RobotIcon.png");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Robot::Start()
{
	CharacterBase::Start();

	m_Radius = ROBOT_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, ROBOT_SIZE_OFFSET);

	m_Active = true;

	if (m_InBattleScene)
	{
		m_MaxHp = ROBOT_MAX_HP;

		m_Speed = ROBOT_MOVE_SPEED;
		m_Hp = m_MaxHp;
		m_Power = ROBOT_DEFAULT_POWER;

		m_SuperAttackPoint = 30;
		m_SkillPointSpend = ROBOT_SKILL_POINT_SPEND;
		m_SuperAttackPointSpend = ROBOT_SUPER_ATTACK_POINT_SPEND;
		m_AttackRange = ROBOT_ATTACK_RANGE;
		m_SuperAttackRange = ROBOT_SUPER_ATTACK_RANGE;

		m_AABB = CollisionManager::GetInstance()->CreateAABB();
		m_AABB->SetTargetPos(&m_Pos);
		m_AABB->SetLocalPos(VGet(0.0f, ROBOT_SIZE.y / 2 * m_Scale.y, 0.0f));

		VECTOR aabbSize = VGet(ROBOT_SIZE.x * m_Scale.x, ROBOT_SIZE.y * m_Scale.y, ROBOT_SIZE.z * m_Scale.z);
		m_AABB->SetSize(aabbSize);

		m_Sphere = CollisionManager::GetInstance()->CreateSphere();
		m_Sphere->SetTargetPos(&m_Pos);
		m_Sphere->SetLocalPos(VGet(0.0f, ROBOT_SIZE.y / 2 * m_Scale.y, 0.0f));
		m_Sphere->SetRadius(ROBOT_SIZE.y * m_Scale.y / 2.0f);
	}

	PlayAnimation(ANIMATION_STOP, true);
}

void Robot::Step()
{
	CharacterBase::Step();

	if (m_ActionType == ACTION_ATTACK)
	{
		if (m_AnimationNowTime == ATTACK_SE_OFFSET)
		{
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_ROBOT_ATTACK);
		}
	}

	if (m_ActionType == ACTION_SUPER_ATTACK)
	{
		if (m_AnimationNowTime == SUPER_ATTACK_SE_OFFSET)
		{
			VECTOR forward = MyMath::VecForwardZX(m_Rot.y);
			VECTOR forwardNorm = VNorm(forward);
			VECTOR forwardDiff = VScale(forwardNorm, SUPER_ATTACK_POS_OFFSET_FORWARD);

			VECTOR heightDiff = VGet(m_Pos.x, m_Pos.y + SUPER_ATTACK_POS_OFFSET_HEIGHT, m_Pos.z);

			VECTOR releasePos = VAdd(forwardDiff, heightDiff);

			BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(ROBOT_BEAM, releasePos, m_Rot);

			bullet->SetShooter(this);

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_ROBOT_SUPER_ATTACK);
		}
	}
}

void Robot::Attack()
{
	CharacterBase::Attack();
}

void Robot::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_ROBOT_SKILL);

		HPHeal(ROBOT_SKILL_HP_HEAL);
	}
}

void Robot::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();
	}
}

