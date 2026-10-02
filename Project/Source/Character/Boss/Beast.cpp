#include "Beast.h"
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
#include "../../MyEffekseer/EffekseerManager.h"

const float BEAST_ROTATION_SPEED = 0.03f;
const float BEAST_MOVE_SPEED = 1.0f;

const float BEAST_SIZE_OFFSET = 1.3f;

const float BEAST_ATTACK_RANGE = 10.0f;
const float BEAST_SUPER_ATTACK_RANGE = 30.0f;
const float ATTACK_SE_OFFSET = 40.0f; // 通常攻撃のSEタイミング補正
const float SUPER_ATTACK_SE_OFFSET = 50.0f; // 必殺技の発射、SEタイミング補正
const float SUPER_ATTACK_POS_OFFSET = 30.0f; // 必殺技の位置補正

const VECTOR BEAST_SIZE = VGet(0.6f, 1.8f, 0.6f);

const int BEAST_DEFAULT_POWER = 10;
const int BEAST_SKILL_POINT_SPEND = 10;
const int BEAST_SUPER_ATTACK_POINT_SPEND = 1;
const int BEAST_MAX_HP = 800;
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
	CharacterBase::Load();

	//m_Handle = MV1LoadModel("Data/Character/Beast.x");

	m_IconHandle = LoadGraph("Data/UI/Character/BeastIcon.png");

	int texHandle = LoadGraph("Data/Character/Beast_diffuse.png");

	//MV1SetTextureGraphHandle(m_Handle, 0, texHandle, true);

	//MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Beast::Start()
{
	CharacterBase::Start();

	m_Radius = BEAST_SIZE.y * m_Scale.y / 2.0f;

	m_Scale = MyMath::VecScale(m_Scale, BEAST_SIZE_OFFSET);

	m_Active = true;

	if (m_InBattleScene)
	{
		m_MaxHp = BEAST_MAX_HP;

		m_Speed = BEAST_MOVE_SPEED;
		m_Hp = m_MaxHp;
		m_Power = BEAST_DEFAULT_POWER;

		m_SuperAttackPoint = 30;
		m_SkillPointSpend = BEAST_SKILL_POINT_SPEND;
		m_SuperAttackPointSpend = BEAST_SUPER_ATTACK_POINT_SPEND;
		m_AttackRange = BEAST_ATTACK_RANGE;
		m_SuperAttackRange = BEAST_SUPER_ATTACK_RANGE;

		/*m_AABB = CollisionManager::GetInstance()->CreateAABB();
		m_AABB->SetTargetPos(&m_Pos);
		m_AABB->SetLocalPos(VGet(0.0f, BEAST_SIZE.y / 2 * m_Scale.y, 0.0f));

		VECTOR aabbSize = VGet(BEAST_SIZE.x * m_Scale.x, BEAST_SIZE.y * m_Scale.y, BEAST_SIZE.z * m_Scale.z);
		m_AABB->SetSize(aabbSize);

		m_Sphere = CollisionManager::GetInstance()->CreateSphere();
		m_Sphere->SetTargetPos(&m_Pos);
		m_Sphere->SetLocalPos(VGet(0.0f, BEAST_SIZE.y / 2 * m_Scale.y, 0.0f));
		m_Sphere->SetRadius(BEAST_SIZE.y * m_Scale.y / 2.0f);*/
	}

	PlayAnimation(ANIMATION_STOP, true);
}

void Beast::Step()
{
	CharacterBase::Step();

	if (m_ActionType == ACTION_ATTACK)
	{
		if (m_AnimationNowTime == ATTACK_SE_OFFSET)
		{
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_BEAST_ATTACK);
		}
	}

	if (m_ActionType == ACTION_SUPER_ATTACK)
	{
		if (m_AnimationNowTime == SUPER_ATTACK_SE_OFFSET)
		{
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_BEAST_SUPER_ATTACK);

			VECTOR jumpWavePosDif = MyMath::VecScale(MyMath::VecForwardZX(m_Rot.y), SUPER_ATTACK_POS_OFFSET);

			VECTOR jumpWavePos = MyMath::VecAdd(m_Pos, jumpWavePosDif);

			BulletBase* bullet = BulletManager::GetInstance()->CreateBullet(BEAST_JUMP_WAVE, jumpWavePos, m_Rot);

			bullet->SetShooter(this);

			EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_BEAST_SUPER_ATTACK, jumpWavePos);
		}
	}
}

void Beast::Update()
{
	CharacterBase::Update();

	VECTOR drawRot = m_Rot;
	drawRot.y += DX_PI_F;

	//MV1SetRotationXYZ(m_Handle, drawRot);

	VECTOR scale = MyMath::VecSame(13.0f);

	//MV1SetScale(m_Handle, scale);
}

void Beast::Attack()
{
	CharacterBase::Attack();
}

void Beast::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		CharacterBase::Skill();

		CreateState(STATE_DESPERATE, 10 * 60);

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_BEAST_SKILL);
	}
}

void Beast::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();
	}
}

