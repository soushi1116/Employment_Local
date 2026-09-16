#pragma once
#include "DxLib.h"
#include "BulletParameter.h"
#include "../Character/CharacterManager.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;
class CharacterBase;

class BulletBase
{
public:
	BulletBase();
	virtual ~BulletBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual void HitCharacter() { m_Active = false; }

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetShooter(CharacterBase* shooter) { m_Shooter = shooter; }

	float GetRadius() { return m_Scale.x; }

	bool IsActive() const { return m_Active; }
	bool IsBoss() const { return m_IsBoss; }

	int GetDamage() { return m_Damage; }
	float GetMagni() { return m_Shooter->GetPowerMagni(); }

	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }
	CharacterBase* GetShooter() { return m_Shooter; }

	BulletType GetType() const { return m_Type; }

	void Delete();

	void HitStage();

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_Dir;

	bool m_Active;
	bool m_IsBoss;

	int m_Handle;
	int m_BornTime;
	int m_Life;
	int m_Damage;

	BulletType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;

	CharacterBase* m_Shooter;
};