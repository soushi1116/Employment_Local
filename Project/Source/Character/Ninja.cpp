#include "Ninja.h"
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
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Bullet/BulletManager.h"

const float NINJA_ROTATION_SPEED = 0.03f;
const float NINJA_MOVE_SPEED = 0.9f;

const float NINJA_SUPER_ATTACK_MOVE_SPEED = 0.3f;

const VECTOR NINJA_SIZE = VGet(0.6f, 1.70f, 0.6f);

const int NINJA_DEFAULT_POWER = 10;
const int NINJA_SKILL_POINT_SPEND = 10;
const int NINJA_SUPER_ATTACK_POINT_SPEND = 10;
const int NINJA_SKILL_INVISIBLE_INTERVAL = 5;

Ninja::Ninja() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 100.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 36.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 68.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 99.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 77.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 32.0f;

	m_InvisibleStartTime = 0;
}

Ninja::~Ninja()
{
	Fin();
}

void Ninja::Init()
{
	m_Type = NINJA;
	CharacterBase::Init();
}

void Ninja::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Ninja.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Ninja::Start()
{
	CharacterBase::Start();

	m_SkillPointSpend = NINJA_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = NINJA_SUPER_ATTACK_POINT_SPEND;

	m_Active = true;

	m_Radius = NINJA_SIZE.y * m_Scale.y / 2.0f;

	m_Speed = NINJA_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = NINJA_DEFAULT_POWER;

	m_SuperAttackPoint = 30;
	m_SkillPoint = 20;

	m_NowAnimation = ANIMATION_STOP;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, NINJA_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(NINJA_SIZE.x * m_Scale.x, NINJA_SIZE.y * m_Scale.y, NINJA_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, NINJA_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(m_Radius);

	PlayAnimation(ANIMATION_STOP, true);
}

void Ninja::Step()
{
	CharacterBase::Step();

	if (m_Invisible)
	{
		FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

		int timeDiff = fps->GetDeltaTime() - m_InvisibleStartTime;

		if (timeDiff > NINJA_SKILL_INVISIBLE_INTERVAL)
		{
			m_Invisible = false;
		}
	}
}

void Ninja::Update()
{
	CharacterBase::Update();

	VECTOR drawRot = m_Rot;
	drawRot.y += DX_PI_F;

	MV1SetRotationXYZ(m_Handle, drawRot);
}

void Ninja::Attack()
{
	CharacterBase::Attack();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_KNIGHT_ATTACK);
}

void Ninja::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		m_Invisible = true;

		FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

		m_InvisibleStartTime = fps->GetDeltaTime();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_KNIGHT_SKILL);
	}
}

void Ninja::SuperAttack()
{
	if (m_SuperAttackPoint > m_SuperAttackPointSpend)
	{
		CharacterBase::SuperAttack();

		VECTOR beamPos = VGet(m_Pos.x, m_Pos.y + 10.0f, m_Pos.z);

		BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(SHURIKEN, beamPos, m_Rot);

		bullet->SetShooter(this);
	}
}

