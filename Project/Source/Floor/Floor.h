#pragma once
#include "DxLib.h"

class CollisionAABB;

class Floor
{
public:
	Floor();
	~Floor();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	VECTOR GetPos() { return m_Pos; }
	int GetHandle() { return m_Handle; }
	int GetCollisionHandle() { return m_CollisionHandle; }
	CollisionAABB* GetAABB() { return m_AABB; }

	MV1_COLL_RESULT_POLY_DIM GetHitResult() const { return m_CollisionResult; }
	MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

private:
	int m_Handle;
	int m_CollisionHandle;
	VECTOR m_Pos;
	CollisionAABB* m_AABB;
	MV1_COLL_RESULT_POLY_DIM m_CollisionResult;
};