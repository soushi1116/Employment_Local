#include "CharacterBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Floor/FloorManager.h"
#include "../Floor/Floor.h"
#include "../Item/ItemManager.h"
#include "../Item/ItemBase.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const int RESPAWN_INTERVAL = 180;
const int PARENT_MAX_HP = 100;
const int CHILD_MAX_HP = 20;

const float ANIMATION_SPEED = 1.0f;

const VECTOR PARENT_DEFAULT_POS = VGet(0.0f, 0.0f, -40.0f);
const VECTOR CHILD_DEFAULT_POS = VGet(20.0f, 0.0f, 40.0f);

CharacterBase::CharacterBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);
	m_DefaultPos = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_Randing = false;
	m_AttackHitFlag = false;
	m_Dead = false;
	m_IsParent = false;
	m_Handle = 0;
	m_Power = 0;
	m_Speed = 0.0f;
	m_Hp = 0;
	m_MaxHp = 0;
	m_RespawnTimer = 0;
	m_Index = 0;
	m_SkillPoint = 0;
	m_SuperAttackPoint = 0;
	m_Gravity = 0.0f;
	m_Type = CHARACTER_TYPE_NONE;
	m_ActionType = ACTION_TYPE_NONE;
	m_AABB = nullptr;
	m_Sphere = nullptr;
	m_AnimTotalTimes[ANIMATION_STOP] = 10.0f;
	m_AnimTotalTimes[ANIMATION_WALK] = 70.0f;
	m_AnimTotalTimes[ANIMATION_ATTACK] = 60.0f;
	m_AnimTotalTimes[ANIMATION_SKILL] = 30.0f;
	m_AnimTotalTimes[ANIMATION_SUPER_ATTACK] = 50.0f;
	m_AnimTotalTimes[ANIMATION_DIE] = 180.0f;
	m_AnimTotalTimes[ANIMATION_DAMAGED] = 30.0f;
	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = ANIMATION_STOP;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Init()
{
	m_IsParent = false;
}

void CharacterBase::Start()
{
	if (m_IsParent)
	{
		m_MaxHp = PARENT_MAX_HP;
	}
	else
	{
		m_MaxHp = CHILD_MAX_HP;
	}

	m_DefaultPos = m_Pos;
}

void CharacterBase::Update()
{
	m_PrevPos = m_Pos;

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	if (m_Pos.y < -50.0f)
	{
		Respawn(m_DefaultPos);
	}

	if (m_Hp <= 0)
	{
		m_RespawnTimer++;

		if (m_RespawnTimer > RESPAWN_INTERVAL)
		{
			Respawn(m_DefaultPos);
			m_RespawnTimer = 0;
		}
	}

	if (CheckHitCoin())
	{
		if (m_SuperAttackPoint <= 100)
		{
			m_SuperAttackPoint++;
		}
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void CharacterBase::DrawModel()
{
	MV1DrawModel(m_Handle);	
}

void CharacterBase::DrawUI()
{
	switch (m_Type)
	{
	case PLAYER:
		DrawFormatString(m_Index * 350 + 100, 800, GetColor(255, 255, 255), "Player[%d, %d, %f]", m_Hp, m_Power, m_Speed);
		DrawBox(200, 50, 600, 80, GetColor(255, 255, 255), TRUE);
		if (m_Hp > 0)
		{
			DrawBox(200, 50, 200 + 400 * m_Hp / m_MaxHp, 80, GetColor(0, 255, 0), TRUE);
		}

		DrawBox(200, 850, 600, 880, GetColor(255, 255, 255), TRUE);
		if (m_SkillPoint > 0)
		{
			DrawBox(200, 850, 200 + 400 * m_SkillPoint / 100, 880, GetColor(0, 255, 255), TRUE);
		}

		DrawBox(700, 850, 1100, 880, GetColor(255, 255, 255), TRUE);
		if (m_SuperAttackPoint > 0)
		{
			DrawBox(700, 850, 700 + 400 * m_SuperAttackPoint / 100, 880, GetColor(255, 255, 0), TRUE);
		}
		break;
	case ENEMY:
		DrawFormatString(m_Index * 350 + 100, 800, GetColor(255, 255, 255), "Enemy[%d, %d, %f]", m_Hp, m_Power, m_Speed);
		break;
	case CHARACTER_TYPE_MAX:
		break;
	case CHARACTER_TYPE_NONE:
		break;
	default:
		break;
	}
}

void CharacterBase::Fin()
{
	MV1DeleteModel(m_Handle);
	m_AABB = nullptr;
	m_Sphere = nullptr;
}

void CharacterBase::Respawn(VECTOR pos)
{
	m_Pos = pos;
	m_Hp = m_MaxHp;
	m_SkillPoint = 0;
	m_SuperAttackPoint = 0;
	m_Dead = false;
	if (m_Sphere != nullptr)
	{
		m_Sphere->SetTargetPos(&m_Pos);
	}
}

void CharacterBase::Attack()
{
	PlayAnimation(ANIMATION_ATTACK, false);
	m_ActionType = ACTION_ATTACK;

	m_AttackHitFlag = true;
}

void CharacterBase::Skill()
{
	if (m_SkillPoint > 10)
	{
		PlayAnimation(ANIMATION_SKILL, false);
		m_ActionType = ACTION_SKILL;
		m_Power++;
		m_SkillPoint -= 10;

		VECTOR playerFootPos = VGet(m_Pos.x, m_Pos.y - m_Scale.y / 2, m_Pos.z);

		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_SKILL, playerFootPos);
	}
}

void CharacterBase::SuperAttack()
{
	if (m_SuperAttackPoint > 10)
	{
		PlayAnimation(ANIMATION_SUPER_ATTACK, false);

		m_ActionType = ACTION_SUPER_ATTACK;
		m_SuperAttackPoint -= 10;
		m_AttackHitFlag = true;
	}
}

void CharacterBase::HitFloor(Floor* floor)
{
	float characterRadius = m_Sphere->GetRadius();

	MV1_COLL_RESULT_POLY_DIM hitResult = floor->CheckCollisionSphere(m_Sphere->GetWorldPos(), m_Sphere->GetRadius());

	for (int i = 0; i < hitResult.HitNum; i++)
	{
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];

		if (polygon.Normal.y <= 0.1f) continue;

		VECTOR spherePos = m_Sphere->GetWorldPos();
		VECTOR lineStart = spherePos;
		VECTOR lineEnd = spherePos;

		lineStart.y += characterRadius;
		lineEnd.y -= characterRadius * 2.0f;

		HITRESULT_LINE lineResult = HitCheck_Line_Triangle(
			lineStart, lineEnd, polygon.Position[0], polygon.Position[1],
			polygon.Position[2]);

		if (!lineResult.HitFlag) continue;

		m_Pos.y = lineResult.Position.y;

		m_Move.y = 0.0f;

		m_Randing = true;
	}

	MV1SetPosition(m_Handle, m_Pos);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterBase::Damage(CharacterBase* opponent)
{
	m_Hp -= opponent->GetPower();

	if (m_Hp > 0)
	{
		PlayAnimation(ANIMATION_DAMAGED, false);

		m_ActionType = ACTION_DAMAGED;
	}
	else
	{
		m_Dead = true;
		PlayAnimation(ANIMATION_DIE, false);
		m_ActionType = ACTION_DIE;
	}
}

void CharacterBase::SetColor()
{
	COLOR_F color = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);

	switch (m_Index)
	{
	case 0:
		color = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		color = GetColorF(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		color = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		color = GetColorF(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}

	SetUseLighting(FALSE);

	MV1SetDifColorScale(m_Handle, color);
}

void CharacterBase::SetPosAndIndex(int index, int parentNum)
{
	m_Index = index;

	if (m_IsParent)
	{
		m_Pos = PARENT_DEFAULT_POS;
	}
	else
	{
		m_Pos = CHILD_DEFAULT_POS;
		if (index < parentNum)
		{
			m_Pos.x -= 20.0f * index;
		}
		else
		{
			m_Pos.x -= 20.0f * (index - 1);
		}
	}
}

bool CharacterBase::CheckHitCoin()
{
	const auto& itemList = ItemManager::GetInstance()->GetItemList();

	bool isAnyHit = false;

	for (auto* item : itemList)
	{
		if (item == nullptr || !item->IsActive()) continue;

		CollisionAABB* coinAABB = item->GetAABB();

		HitResultAABB result = m_AABB->CheckAABB(coinAABB);

		if (result.m_IsHit)
		{
			m_SuperAttackPoint += 10;

			item->Delete();

			isAnyHit = true;
		}
	}

	return isAnyHit;
}

void CharacterBase::PlayAnimation(CharacterAnimationType anim, bool isLoop)
{
	if (anim == m_NowAnimation) return;

	MV1DetachAnim(m_Handle, m_AnimationAttachIndex);

	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	m_AnimationTotalTime = m_AnimTotalTimes[anim];

	m_AnimationNowTime = 0.0f;

	m_IsLoopAnimation = isLoop;

	m_NowAnimation = anim;
}

void CharacterBase::UpdateAnimation()
{
	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);

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

			PlayAnimation(ANIMATION_STOP, true);

		}
	}
}