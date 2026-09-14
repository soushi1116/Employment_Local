#include "Fairy.h"
#include <math.h>
#include "../CharacterParameter.h"
#include "../../Input/Input.h"
#include "../../MyMath/MyMath.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"
#include "../../Collision/CollisionSphere.h"
#include "../../Camera/CameraManager.h"
#include "../../Camera/CameraBase.h"
#include "../../MyEffekseer/EffekseerManager.h"
#include "../../MyEffekseer/EffekseerEffect.h"
#include "../../Sound/SoundManager.h"
#include "../../Bullet/BulletManager.h"

const float FAIRY_ROTATION_SPEED = 0.03f;
const float FAIRY_MOVE_SPEED = 0.7f;

const float SUPER_ATTACK_SE_OFFSET = 40.0f; // •KŽE‹Z‚Ì”­ŽËASEƒ^ƒCƒ~ƒ“ƒO•â³
const float SUPER_ATTACK_POS_OFFSET_FORWARD = 15.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‘O•û•â³
const float SUPER_ATTACK_POS_OFFSET_HEIGHT = 10.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‚‚³•â³

const VECTOR FAIRY_SIZE = VGet(0.6f, 1.70f, 0.6f);

const float FAIRY_ATTACK_RANGE = 100.0f;
const float FAIRY_SUPER_ATTACK_RANGE = 100.0f;

const int FAIRY_DEFAULT_POWER = 10;
const int FAIRY_SKILL_POINT_SPEND = 10;
const int FAIRY_SUPER_ATTACK_POINT_SPEND = 10;
const int FAIRY_MAX_HP = 20;

Fairy::Fairy() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 110.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 33.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 71.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 73.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 180.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 30.0f;
	m_AnimTotalTimes[ANIMATION_RUN] = 21.0f;
}

Fairy::~Fairy()
{
	Fin();
}

void Fairy::Init()
{
	m_Type = FAIRY;
	CharacterBase::Init();
}

void Fairy::Load()
{
	CharacterBase::Load();

	m_Handle = MV1LoadModel("Data/Character/Fairy.x");

	m_IconHandle = LoadGraph("Data/UI/Character/FailyIcon.png");

	int texHandle = LoadGraph("Data/Character/Fairy_diffuse.png");

	MV1SetTextureGraphHandle(m_Handle, 0, texHandle, true);

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Fairy::Start()
{
	CharacterBase::Start();

	m_Active = true;

	m_Radius = FAIRY_SIZE.y * m_Scale.y / 2.0f;

	if (m_InBattleScene)
	{
		m_MaxHp = FAIRY_MAX_HP;

		m_SkillPointSpend = FAIRY_SKILL_POINT_SPEND;
		m_SuperAttackPointSpend = FAIRY_SUPER_ATTACK_POINT_SPEND;
		m_AttackRange = FAIRY_ATTACK_RANGE;
		m_SuperAttackRange = FAIRY_SUPER_ATTACK_RANGE;

		m_Speed = FAIRY_MOVE_SPEED;
		m_Hp = m_MaxHp;
		m_Power = FAIRY_DEFAULT_POWER;

		m_SuperAttackPoint = 30;

		m_NowAnimation = ANIMATION_STOP;

		m_AABB = CollisionManager::GetInstance()->CreateAABB();
		m_AABB->SetTargetPos(&m_Pos);
		m_AABB->SetLocalPos(VGet(0.0f, FAIRY_SIZE.y / 2 * m_Scale.y, 0.0f));

		VECTOR aabbSize = VGet(FAIRY_SIZE.x * m_Scale.x, FAIRY_SIZE.y * m_Scale.y, FAIRY_SIZE.z * m_Scale.z);
		m_AABB->SetSize(aabbSize);

		m_Sphere = CollisionManager::GetInstance()->CreateSphere();
		m_Sphere->SetTargetPos(&m_Pos);
		m_Sphere->SetLocalPos(VGet(0.0f, FAIRY_SIZE.y / 2 * m_Scale.y, 0.0f));
		m_Sphere->SetRadius(m_Radius);
	}

	PlayAnimation(ANIMATION_STOP, true);
}

void Fairy::Step()
{
	CharacterBase::Step();

	if (m_SkillPoint >= FAIRY_SKILL_POINT_SPEND)
	{
		int random = GetRand(100);

		if (random > 80)
		{
			m_SkillFlag = true;
		}
	}

	if (m_ActionType == ACTION_ATTACK)
	{
		if (m_AnimationNowTime == SUPER_ATTACK_SE_OFFSET)
		{
			VECTOR forward = MyMath::VecForwardZX(m_Rot.y);
			VECTOR forwardNorm = VNorm(forward);
			VECTOR forwardDiff = VScale(forwardNorm, SUPER_ATTACK_POS_OFFSET_FORWARD);

			VECTOR heightDiff = VGet(m_Pos.x, m_Pos.y + SUPER_ATTACK_POS_OFFSET_HEIGHT, m_Pos.z);

			VECTOR releasePos = VAdd(forwardDiff, heightDiff);

			BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(NORMAL_LEAF, releasePos, m_Rot);

			bullet->SetShooter(this);

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_NINJA_SUPER_ATTACK);
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

			BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(POISON_LEAF, releasePos, m_Rot);

			bullet->SetShooter(this);

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_NINJA_SUPER_ATTACK);
		}
	}
}

void Fairy::Update()
{
	CharacterBase::Update();

	VECTOR drawRot = m_Rot;
	drawRot.y += DX_PI_F;

	MV1SetRotationXYZ(m_Handle, drawRot);
}

void Fairy::Attack()
{
	CharacterBase::Attack();
}

void Fairy::Skill()
{
	if (m_SkillPoint > 10)
	{
		CharacterBase::Skill();

		m_Power++;

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_KNIGHT_SKILL);
	}
}

void Fairy::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();
	}
}

