#include "CharacterBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Floor/FloorManager.h"
#include "../Floor/Floor.h"

CharacterBase::CharacterBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_Randing = false;
	m_AttackHitFlag = false;
	m_Handle = 0;
	m_Power = 0;
	m_Speed = 0.0f;
	m_Hp = 0;
	m_Gravity = 0.0f;
	m_Type = CHARACTER_TYPE_NONE;
	m_AABB = nullptr;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Update()
{
	m_PrevPos = m_Pos;

	if (m_Pos.y < -50.0f)
	{
		m_Pos = VGet(0.0f, 0.0f, 0.0f);
	}

	MoveWithCollision();

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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "À•W[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "ˆÚ“®[%f, %f, %f]", m_Move.x, m_Move.y, m_Move.z);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "‰ñ“][%f, %f, %f]", m_Rot.x, m_Rot.y, m_Rot.z);

	switch (m_Type)
	{
	case PLAYER:
		DrawFormatString(1000, 800, GetColor(255, 255, 255), "Player[%d, %d, %f]", m_Hp, m_Power, m_Speed);
		if (GetAttackHitFlag())
		{
			// ƒqƒbƒg’†‚È‚ç‰æ–Ê¶ã‚ÉuÔ‚¢ŽlŠpv‚ð•`‚­
			DrawBox(10, 10, 50, 50, GetColor(255, 0, 0), TRUE);
		}
		else
		{
			// •½íŽž‚Íu”’‚¢ŽlŠpv‚ð•`‚­
			DrawBox(10, 10, 50, 50, GetColor(255, 255, 255), TRUE);
		}
		break;
	case ENEMY:
	{
		DrawFormatString(0, 800, GetColor(255, 255, 255), "Enemy[%d, %d, %f]", m_Hp, m_Power, m_Speed);
	}
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
}

void CharacterBase::MoveWithCollision()
{
	// x
	m_Pos.x += m_Move.x;

	Floor* floor = FloorManager::GetInstance()->GetFloor();

	CollisionAABB* floorAABB = floor->GetAABB();
	const HitResultAABB resultX = m_AABB->CheckAABB(floorAABB);

	if (resultX.m_IsHit)
	{
		if (m_Move.x > 0.0f)
		{
			m_Pos.x -= m_AABB->GetRight() - resultX.m_HitLeft;
		}
		else if (m_Move.x < 0.0f)
		{
			m_Pos.x += resultX.m_HitRight - m_AABB->GetLeft();
		}

		m_Move.x = 0.0f;
	}

	// y
	m_Pos.y += m_Move.y;

	const HitResultAABB resultY = m_AABB->CheckAABB(floorAABB);

	if (resultY.m_IsHit)
	{
		if (m_Move.y > 0.0f)
		{
			m_Pos.y -= m_AABB->GetTop() - resultY.m_HitBottom;
		}
		else if (m_Move.y < 0.0f)
		{
			m_Pos.y += resultY.m_HitTop - m_AABB->GetBottom();
			m_Randing = true;
		}

		m_Move.y = 0.0f;
		m_Gravity = 0.0f;
	}
	else
	{
		if (m_Randing) 
		{
			m_Randing = false;
		}
	}

	// z
	m_Pos.z += m_Move.z;

	const HitResultAABB resultZ = m_AABB->CheckAABB(floorAABB);

	if (resultZ.m_IsHit)
	{
		if (m_Move.z > 0.0f)
		{
			m_Pos.z -= m_AABB->GetBack() - resultZ.m_HitFront;
		}
		else if (m_Move.x < 0.0f)
		{
			m_Pos.z += resultZ.m_HitBack - m_AABB->GetFront();
		}

		m_Move.z = 0.0f;
	}
}