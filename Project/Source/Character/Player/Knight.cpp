#include "Knight.h"
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

const float KNIGHT_ROTATION_SPEED = 0.03f;
const float KNIGHT_MOVE_SPEED = 0.7f;

const float KNIGHT_SUPER_ATTACK_MOVE_SPEED = 0.3f;
const float KNIGHT_ATTACK_RANGE = 10.0f;
const float KNIGHT_SUPER_ATTACK_RANGE = 20.0f;

const VECTOR KNIGHT_SIZE = VGet(0.6f, 1.70f, 0.6f);

const VECTOR SWORD_POS_OFFSET = VGet(2.0f, 3.0f, 4.0f);
const VECTOR SWORD_COLLISION_SIZE = VGet(1.0f, 10.0f, 6.0f);

const int KNIGHT_DEFAULT_POWER = 10;
const int KNIGHT_SKILL_POINT_SPEND = 10;
const int KNIGHT_SUPER_ATTACK_POINT_SPEND = 10;
const int KNIGHT_MAX_HP = 40;

Knight::Knight() : CharacterBase()
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

Knight::~Knight()
{
	Fin();
}

void Knight::Init()
{
	m_Type = KNIGHT;
	CharacterBase::Init();
}

void Knight::Load()
{
	CharacterBase::Load();

	m_Handle = MV1LoadModel("Data/Character/Knight.x");

	m_IconHandle = LoadGraph("Data/UI/Character/KnightIcon.png");

	int texHandle = LoadGraph("Data/Character/Knight_diffuse.png");

	MV1SetTextureGraphHandle(m_Handle, 0, texHandle, true);

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Knight::Start()
{
	CharacterBase::Start();

	m_MaxHp = KNIGHT_MAX_HP;

	m_SkillPointSpend = KNIGHT_SKILL_POINT_SPEND;
	m_SuperAttackPointSpend = KNIGHT_SUPER_ATTACK_POINT_SPEND;
	m_AttackRange = KNIGHT_ATTACK_RANGE;
	m_SuperAttackRange = KNIGHT_SUPER_ATTACK_RANGE;

	m_Active = true;

	m_Radius = KNIGHT_SIZE.y * m_Scale.y / 2.0f;

	m_Speed = KNIGHT_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = KNIGHT_DEFAULT_POWER;

	m_SuperAttackPoint = 30;

	m_NowAnimation = ANIMATION_STOP;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, KNIGHT_SIZE.y / 2 * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(KNIGHT_SIZE.x * m_Scale.x, KNIGHT_SIZE.y * m_Scale.y, KNIGHT_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, KNIGHT_SIZE.y / 2 * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(m_Radius);

	PlayAnimation(ANIMATION_STOP, true);
}

void Knight::Step()
{
	CharacterBase::Step();

	if (!m_Dead)
	{
		if (m_ActionType == ACTION_SUPER_ATTACK)
		{
			m_Move.x = KNIGHT_SUPER_ATTACK_MOVE_SPEED * sinf(m_Rot.y);
			m_Move.z = KNIGHT_SUPER_ATTACK_MOVE_SPEED * cosf(m_Rot.y);
		}
	}

	if (m_SkillPoint >= KNIGHT_SKILL_POINT_SPEND)
	{
		int random = GetRand(100);

		if (random > 80)
		{
			m_SkillFlag = true;
		}
	}
}

void Knight::Attack()
{
	CharacterBase::Attack();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlaySE(SE_KNIGHT_ATTACK);
}

void Knight::Skill()
{
	if (m_SkillPoint > 10)
	{
		CharacterBase::Skill();

		m_Power++;

		VECTOR footPos = VGet(m_Pos.x, m_Pos.y - m_Scale.y / 2, m_Pos.z);

		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_SKILL, footPos);

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_KNIGHT_SKILL);
	}
}

void Knight::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		CharacterBase::SuperAttack();

		/*EffekseerEffect* effect = EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_KNIGHT_SUPER_ATTACK, m_Pos);
		effect->SetParentCharacter(this);*/

		Sound* sound = SoundManager::GetInstance()->GetSound();
		sound->PlaySE(SE_KNIGHT_SUPER_ATTACK);
	}
}

