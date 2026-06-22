#include "Enemy.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const VECTOR ENEMY_SIZE = VGet(4.0f, 11.2f, 4.0f);
const VECTOR ENEMY_DEFAULT_POS = VGet(20.0f, 0.0f, 20.0f);

const float ENEMY_GRAVITY = 0.01f;
const float ENEMY_MOVE_SPEED = 0.1f;

const int ENEMY_HP_MAX = 20;
const int ENEMY_DEFAULT_POWER = 10;

const float ANIMATION_SPEED = 1.0f;

Enemy::Enemy() : CharacterBase()
{
	m_MaxHp = ENEMY_HP_MAX;
	m_DefaultPos = ENEMY_DEFAULT_POS;
	m_MoveDir = 0;

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
	m_AnimTotalTimes[ENEMY_ANIMATION_DIE] = 180.0f;
	m_AnimTotalTimes[ENEMY_ANIMATION_DAMAGED] = 30.0f;
}

Enemy::~Enemy()
{
	Fin();
}

void Enemy::Init()
{
	CharacterBase::Init();
}

void Enemy::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Enemy::Start()
{
	CharacterBase::Start();

	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	if (m_IsParent)
	{
		m_Scale = MyMath::VecScale(m_Scale, 1.2f);
	}

	m_Active = true;

	m_Type = ENEMY;

	m_Hp = m_MaxHp;
	m_Power = ENEMY_DEFAULT_POWER;

	m_Pos = m_DefaultPos;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(ENEMY_SIZE.x * m_Scale.x, ENEMY_SIZE.y * m_Scale.y, ENEMY_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(ENEMY_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ENEMY_ANIMATION_STOP, true);
}

void Enemy::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Move.y = m_Gravity;

	if (!m_Dead && m_ActionType == ACTION_TYPE_NONE && m_Randing)
	{
		/*switch (m_MoveDir)
		{
		case 0:
			m_Move.z = -ENEMY_MOVE_SPEED;
			if (m_Pos.z < -ENEMY_DEFAULT_POS.z)
			{
				m_MoveDir = 1;
			}
			break;
		case 1:
			m_Move.x = -ENEMY_MOVE_SPEED;
			if (m_Pos.x < -ENEMY_DEFAULT_POS.x)
			{
				m_MoveDir = 2;
			}
			break;
		case 2:
			m_Move.z = ENEMY_MOVE_SPEED;
			if (m_Pos.z > ENEMY_DEFAULT_POS.x)
			{
				m_MoveDir = 3;
			}
			break;
		case 3:
			m_Move.x = ENEMY_MOVE_SPEED;
			if (m_Pos.x > ENEMY_DEFAULT_POS.z)
			{
				m_MoveDir = 0;
			}
			break;
		default:
			break;
		}*/

		if (m_Move.x == 0.0f && m_Move.z == 0.0f)
		{
			PlayAnimation(ENEMY_ANIMATION_STOP, true);
		}
		else
		{
			PlayAnimation(ENEMY_ANIMATION_WALK, true);
			m_Rot.y = atan2f(m_Move.x, m_Move.z);
		}
	}

	m_Move.y = m_Gravity;

	if (m_Randing)
	{
		m_Gravity = 0.0f;

		m_Move.y = -0.0001f;
	}
	else
	{
		m_Gravity -= ENEMY_GRAVITY;
		m_Move.y = m_Gravity;
	}

	m_Randing = false;

	UpdateAnimation();
}

void Enemy::Damage(CharacterBase* opponent)
{
	CharacterBase::Damage(opponent);

	if (m_Hp > 0)
	{
		PlayAnimation(ENEMY_ANIMATION_DAMAGED, false);

		m_ActionType = ACTION_DAMAGED;
	}
	else
	{
		m_Dead = true;
		m_MoveDir = 0;
		PlayAnimation(ENEMY_ANIMATION_DIE, false);
		m_ActionType = ACTION_DIE;
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
			m_ActionType = ACTION_TYPE_NONE;
		}
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;

			m_ActionType = ACTION_TYPE_NONE;

			PlayAnimation(ENEMY_ANIMATION_STOP, true);

			return;
		}
	}

	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);
}

