#pragma once
#include "DxLib.h"
#include "BulletParameter.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;

class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }

	float GetRadius() { return 5.0f; }

	bool IsActive() const { return m_Active; }

	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	BulletType GetType() const { return m_Type; }

	void Delete();

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;

	bool m_Active;

	int m_Handle;

	BulletType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;
};