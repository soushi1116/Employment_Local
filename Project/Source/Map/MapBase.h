#pragma once
#include "DxLib.h"
#include "MapParameter.h"

class CollisionAABB;

class MapBase
{
public:
	MapBase();
	~MapBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

public:
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetScale() { return m_Scale; }
	int GetHandle() { return m_Handle; }
	int GetCollisionHandle() { return m_CollisionHandle; }
	CollisionAABB* GetAABB() { return m_AABB; }

	MapType GetType() { return m_Type; }

	MV1_COLL_RESULT_POLY_DIM GetHitResult() const { return m_CollisionResult; }
	MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

protected:
	int m_Handle;
	int m_CollisionHandle;
	VECTOR m_Pos;
	VECTOR m_Scale;
	CollisionAABB* m_AABB;
	MV1_COLL_RESULT_POLY_DIM m_CollisionResult;

	MapType m_Type;
};