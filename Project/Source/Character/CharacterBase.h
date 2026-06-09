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

	CollisionAABB* GetAABB() { return m_AABB; }

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;

	bool m_Active;
	bool m_Randing;

	int m_Handle;

	float m_Gravity;

	CharacterType m_Type;

	CollisionAABB* m_AABB;

};