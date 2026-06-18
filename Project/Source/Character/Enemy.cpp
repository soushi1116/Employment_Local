#include "Enemy.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const VECTOR ENEMY_SIZE = VGet(4.0f, 11.2f, 4.0f);

const float ENEMY_GRAVITY = 0.01f;

const int ENEMY_HP_MAX = 100;
const int ENEMY_DEFAULT_POWER = 10;

const float ANIMATION_SPEED = 1.0f;

Enemy::Enemy() : CharacterBase()
{
	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = ENEMY_ANIMATION_STOP;

	m_AnimTotalTimes[ENEMY_ANIMATION_STOP] = 10.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_WALK] = 70.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_ATTACK] = 30.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_SKILL] = 30.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_SUPER_ATTACK] = 50.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_DIE] = 40.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_DAMAGED] = 30.0f;
}

Enemy::~Enemy()
{
	Fin();
}

void Enemy::Init()
{

}

void Enemy::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Enemy::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;

	m_Type = ENEMY;

	m_Hp = ENEMY_HP_MAX;
	m_Power = ENEMY_DEFAULT_POWER;

	m_Pos = VGet(0.0f, 0.0f, 5.0f);
	m_Rot = VGet(0.0f, DX_PI_F, 0.0f);

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.7f, 0.0f));
	m_AABB->SetSize(ENEMY_SIZE);

	PlayAnimation(ENEMY_ANIMATION_STOP, true);
}

void Enemy::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Move.y = m_Gravity;

	if (!m_Randing) m_Gravity -= ENEMY_GRAVITY;

	UpdateAnimation();
}

void Enemy::Damage()
{
	m_Hp -= 10;

	if (m_Hp > 0)
	{
		PlayAnimation(ENEMY_ANIMATION_DAMAGED, false);
	}
	else
	{
		PlayAnimation(ENEMY_ANIMATION_DIE, false);
	}
}

void Enemy::PlayAnimation(EnemyAnimationType anim, bool isLoop)
{
	if (anim == m_NowAnimation) return;

	if (m_AnimationAttachIndex <= 0)
	{
		MV1DetachAnim(m_Handle, m_AnimationAttachIndex);
	}

	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	m_AnimationTotalTime = m_AnimTotalTimes[anim];

	m_AnimationNowTime = 0.0f;

	m_IsLoopAnimation = isLoop;

	m_NowAnimation = anim;
}

void Enemy::UpdateAnimation()
{
	m_AnimationNowTime += ANIMATION_SPEED;

	if (m_AnimationNowTime > m_AnimationTotalTime)
	{
		if (m_IsLoopAnimation)
		{
			m_AnimationNowTime = 0.0f;
		}
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;

			PlayAnimation(ENEMY_ANIMATION_STOP, true);

			return;
		}
	}

	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);
}