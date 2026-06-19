#include "CharacterBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Floor/FloorManager.h"
#include "../Floor/Floor.h"

const int RESPAWN_INTERVAL = 180;

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
	m_Handle = 0;
	m_Power = 0;
	m_Speed = 0.0f;
	m_Hp = 0;
	m_MaxHp = 0;
	m_RespawnTimer = 0;
	m_Gravity = 0.0f;
	m_Type = CHARACTER_TYPE_NONE;
	m_ActionType = ACTION_TYPE_NONE;
	m_AABB = nullptr;
	m_Sphere = nullptr;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Update()
{
	m_PrevPos = m_Pos;

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	if (m_Pos.y < -50.0f)
	{
		m_Pos = VGet(0.0f, 0.0f, 0.0f);
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

void CharacterBase::Respawn(VECTOR pos)
{
	m_Pos = pos;
	m_Hp = m_MaxHp;
	m_Dead = false;
	if (m_Sphere != nullptr)
	{
		m_Sphere->SetTargetPos(&m_Pos);
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
}