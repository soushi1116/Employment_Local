#pragma once
#include "DxLib.h"
#include "CharacterParameter.h"

class CollisionAABB;
struct HitResultAABB;

class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual void MoveWithCollision();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }

	float GetRadius() { return 5.0f; }

	CollisionAABB* GetAABB() { return m_AABB; }

	int GetHandle() { return m_Handle; }

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;

	bool m_Active;
	bool m_Randing;

	int m_Handle;
	int m_Power;
	int m_Hp;

	float m_Speed;

	float m_Gravity;

	CharacterType m_Type;

	CollisionAABB* m_AABB;

};