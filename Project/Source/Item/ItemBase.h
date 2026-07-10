#pragma once
#include "DxLib.h"
#include "ItemParameter.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;

class ItemBase
{
public:
	ItemBase();
	virtual ~ItemBase();

public:
	virtual void Init() = 0;
	virtual void Load(int baseHandle) = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }

	void SetPos(VECTOR pos) { m_Pos = pos; }

	float GetRadius() { return 5.0f; }

	bool IsActive() const { return m_Active; }

	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	ItemType GetType() const { return m_Type; }

	void Delete();

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;

	bool m_Active;

	int m_Handle;

	ItemType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;
};