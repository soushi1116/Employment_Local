#pragma once
#include "DxLib.h"
#include "CharacterParameter.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;
class Floor;

enum ActionType
{
	ACTION_TYPE_NONE,
	ACTION_ATTACK,
	ACTION_SKILL,
	ACTION_SUPER_ATTACK,
	ACTION_DAMAGED,
	ACTION_DIE,
	ACTION_TYPE_MAX
};

class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void DrawModel();
	virtual void DrawUI();
	virtual void Fin();

	virtual void Respawn(VECTOR pos);

	virtual void HitFloor(Floor* floor);

	virtual void Damage(CharacterBase* opponent);

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }

	float GetRadius() { return 5.0f; }

	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	int GetHandle() { return m_Handle; }
	int GetPower() { return m_Power; }

	CharacterType GetType() const { return m_Type; }

	void AttackHitFlagTrue() { if (!m_AttackHitFlag) m_AttackHitFlag = true; }
	void AttackHitFlagFalse() { if (m_AttackHitFlag) m_AttackHitFlag = false; }

	bool GetAttackHitFlag() { return m_AttackHitFlag; }
	
	ActionType GetActionType() { return m_ActionType; }

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;
	VECTOR m_DefaultPos;

	bool m_Active;
	bool m_Randing;
	bool m_AttackHitFlag;
	bool m_Dead;

	int m_Handle;
	int m_Power;
	int m_Hp;
	int m_MaxHp;
	int m_RespawnTimer;

	float m_Speed;

	float m_Gravity;

	CharacterType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;

	ActionType m_ActionType;
};