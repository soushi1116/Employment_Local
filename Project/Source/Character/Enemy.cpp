#include "Enemy.h"
#include "CharacterParameter.h"
#include "CharacterManager.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const VECTOR ENEMY_SIZE = VGet(4.0f, 11.2f, 4.0f);

const float ENEMY_GRAVITY = 0.01f;
const float ENEMY_MOVE_SPEED = 0.1f;

const int ENEMY_DEFAULT_POWER = 10;

const float ANIMATION_SPEED = 1.0f;

Enemy::Enemy() : CharacterBase()
{
	
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

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));

	VECTOR aabbSize = VGet(ENEMY_SIZE.x * m_Scale.x, ENEMY_SIZE.y * m_Scale.y, ENEMY_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 5.5f * m_Scale.y, 0.0f));
	m_Sphere->SetRadius(ENEMY_SIZE.y * m_Scale.y / 2.0f);

	PlayAnimation(ANIMATION_STOP, true);
}

void Enemy::Step()
{
	if (!m_InBattleScene)
	{
		PlayAnimation(ANIMATION_STOP, true);
		return;
	}

	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Move.y = m_Gravity;

	if (!m_Dead && m_Randing)
	{
		AutoMove();

		if (m_ActionType == ACTION_TYPE_NONE)
		{
			if (m_Move.x == 0.0f && m_Move.z == 0.0f)
			{
				PlayAnimation(ANIMATION_STOP, true);
			}
			else
			{
				PlayAnimation(ANIMATION_WALK, true);
				m_Rot.y = atan2f(m_Move.x, m_Move.z);
			}
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

void Enemy::AutoMove()
{
	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	CharacterBase* target = nullptr;

	VECTOR targetVec = VGet(0.0f, 0.0f, 0.0f);

	if (m_IsParent)
	{
		for (auto character : characterList)
		{
			if (character->IsParent()) continue;

			if (target == nullptr)
			{
				target = character;
			}
			else
			{
				VECTOR currentVec = MyMath::VecCreate(m_Pos, character->GetPos());

				if (MyMath::VecLong(currentVec) <= MyMath::VecLong(targetVec))
				{
					target = character;
				}

				targetVec = MyMath::VecCreate(m_Pos, target->GetPos());
			}
		}
	}
	else
	{
		for (auto character : characterList)
		{
			if (character->IsParent())
			{
				target = character;

				targetVec = MyMath::VecCreate(m_Pos, target->GetPos());
			}
		}
	}

	m_Rot.y = atan2f(targetVec.x, targetVec.z);

	if (MyMath::VecLong(targetVec) >= 5.0f)
	{
		m_Move.x = ENEMY_MOVE_SPEED * sinf(m_Rot.y);
		m_Move.z = ENEMY_MOVE_SPEED * cosf(m_Rot.y);
	}
	else
	{
		if (m_ActionType == ACTION_TYPE_NONE)
		{
			Attack();
		}
	}
}


