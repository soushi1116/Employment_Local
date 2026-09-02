#include "Ninja.h"
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
#include "../../FPS/FPSManager.h"
#include "../../Bullet/BulletManager.h"

const float NINJA_ROTATION_SPEED = 0.03f; // ‰ñ“]‘¬“x
const float NINJA_MOVE_SPEED = 0.9f; // Å‚ˆÚ“®‘¬“x

const float ATTACK_SE_OFFSET = 30.0f; // ’ÊíUŒ‚‚ÌSEƒ^ƒCƒ~ƒ“ƒO•â³
const float SUPER_ATTACK_SE_OFFSET = 40.0f; // •KŽE‹Z‚Ì”­ŽËASEƒ^ƒCƒ~ƒ“ƒO•â³
const float SUPER_ATTACK_POS_OFFSET_FORWARD = 15.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‘O•û•â³
const float SUPER_ATTACK_POS_OFFSET_HEIGHT = 10.0f; // •KŽE‹Z‚Ì”­ŽËˆÊ’u‚Ì‚‚³•â³

const float NINJA_ATTACK_RANGE = 10.0f; // UŒ‚‚ðŒJ‚èo‚·‹——£(CPU)
const float NINJA_SUPER_ATTACK_RANGE = 100.0f; // •KŽE‹Z‚ðŒJ‚èo‚·‹——£(CPU)

const VECTOR NINJA_SIZE = VGet(0.6f, 1.70f, 0.6f); // ƒTƒCƒY

const int NINJA_DEFAULT_POWER = 10; // UŒ‚—Í‚Ì‰Šú’l
const int NINJA_SKILL_POINT_SPEND = 10; // Á”ïƒXƒLƒ‹ƒ|ƒCƒ“ƒg
const int NINJA_SUPER_ATTACK_POINT_SPEND = 1; // Á”ï•KŽE‹Zƒ|ƒCƒ“ƒg
const int NINJA_SKILL_INVISIBLE_INTERVAL = 5; // ƒXƒLƒ‹‚É‚æ‚é“§–¾ŽžŠÔ
const int NINJA_MAX_HP = 30;

Ninja::Ninja() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 100.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 36.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 68.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 99.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 77.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 32.0f;
	m_AnimTotalTimes[ANIMATION_RUN] = 19.0f;

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
	CharacterBase::Load();

	m_Handle = MV1LoadModel("Data/Character/Ninja.x");

	m_IconHandle = LoadGraph("Data/UI/Character/NinjaIcon.png");

	int texHandle = LoadGraph("Data/Character/Ninja_diffuse.png");

	MV1SetTextureGraphHandle(m_Handle, 0, texHandle, true);

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Ninja::Start()
{
	CharacterBase::Start();

	m_MaxHp = NINJA_MAX_HP;

	m_SkillPointSpend = NINJA_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = NINJA_SUPER_ATTACK_POINT_SPEND;
	m_AttackRange = NINJA_ATTACK_RANGE;
	m_SuperAttackRange = NINJA_SUPER_ATTACK_RANGE;

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
	
	if (m_ActionType == ACTION_ATTACK)
	{
		if (m_AnimationNowTime == ATTACK_SE_OFFSET)
		{
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_NINJA_ATTACK);
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

			BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(SHURIKEN, releasePos, m_Rot);

			bullet->SetShooter(this);

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_NINJA_SUPER_ATTACK);
		}
	}
}

void Ninja::Update()
{
	CharacterBase::Update();

	VECTOR drawRot = m_Rot;
	drawRot.y += DX_PI_F;

	MV1SetRotationXYZ(m_Handle, drawRot);

	//VECTOR scale = VGet(0.1f, 0.1f, 0.1f);

	//MV1SetScale(m_Handle, scale);
}

void Ninja::Attack()
{
	CharacterBase::Attack();

	/*Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_NINJA_ATTACK);*/
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
		sound->PlaySE(SE_NINJA_SKILL);
	}
}

void Ninja::SuperAttack()
{
	if (m_SuperAttackPoint > m_SuperAttackPointSpend)
	{
		CharacterBase::SuperAttack();
	}
}

