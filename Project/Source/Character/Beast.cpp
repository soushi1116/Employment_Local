#include "Beast.h"
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

const float BEAST_ROTATION_SPEED = 0.03f;
const float BEAST_MOVE_SPEED = 0.5f;

const float BEAST_SIZE_OFFSET = 1.3f;

const VECTOR BEAST_SIZE = VGet(0.6f, 1.8f, 0.6f);

const int BEAST_DEFAULT_POWER = 10;
const int BEAST_SKILL_POINT_SPEND = 10;
const int BEAST_SUPER_ATTACK_POINT_SPEND = 10;
const float BEAST_SKILL_POWER_UP = 1.5f;

Beast::Beast() : CharacterBase()
{
	m_AnimTotalTimes[ANIMATION_STOP] = 121.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 43.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 100.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 71.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 111.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 138.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 60.0f;
	m_AnimTotalTimes[ANIMATION_RUN] = 26.0f;
}

Beast::~Beast()
{
	Fin();
}

void Beast::Init()
{
	m_Type = BEAST;
	CharacterBase::Init();
}

void Beast::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Beast.x");

	int texHandle = LoadGraph("Data/Character/Beast_diffuse.png");

	MV1SetTextureGraphHandle(m_Handle, 0, texHandle, true);

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Beast::Start()
{
	CharacterBase::Start();

	m_Radius = BEAST_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, BEAST_SIZE_OFFSET);

	m_Active = true;

	m_Speed = BEAST_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = BEAST_DEFAULT_POWER;

	m_SuperAttackPoint = 30;
	m_SkillPointSpend = BEAST_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = BEAST_SUPER_ATTACK_POINT_SPEND;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, BEAST_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(BEAST_SIZE.x * m_Scale.x, BEAST_SIZE.y * m_Scale.y, BEAST_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, BEAST_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(BEAST_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Beast::Step()
{
	CharacterBase::Step();
}

void Beast::Update()
{
	CharacterBase::Update();

	VECTOR drawRot = m_Rot;
	drawRot.y += DX_PI_F;

	MV1SetRotationXYZ(m_Handle, drawRot);

	VECTOR scale = MyMath::VecSame(13.0f);

	MV1SetScale(m_Handle, scale);
}

void Beast::Attack()
{
	CharacterBase::Attack();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_BEAST_ATTACK);
}

void Beast::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_BEAST_SKILL);

		m_Power *= BEAST_SKILL_POWER_UP;
	}
}

void Beast::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_BEAST_SUPER_ATTACK);
	}
}

