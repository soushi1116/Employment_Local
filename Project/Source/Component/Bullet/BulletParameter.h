#pragma once

#include "DxLib.h"
#include <memory>
#include "../Component.h"

class GameObject;
class Physics3D;

enum BulletType
{
	BULLET_TYPE_SHURIKEN,
	BULLET_TYPE_NORMAL_LEAF,
	BULLET_TYPE_POISON_LEAF,

	BULLET_TYPE_MAX,
	BULLET_TYPE_NONE = -1
};

class BulletParameter : public Component
{
public:
	BulletParameter(GameObject* owner);
	~BulletParameter();

public:
	virtual void Step();

public:
	void SetType(BulletType type) { m_Type = type; }
	void SetSpeed(float speed) { m_MoveSpeed = speed; }
	void SetPhysics(std::shared_ptr<Physics3D> physics) { m_Physics = physics; }

	BulletType GetType() const { return m_Type; }
	float GetSpeed() const { return m_MoveSpeed; }

private:
	BulletType m_Type;

	float m_MoveSpeed;

	float m_LifeLimit;
	float m_LifeTimer;

	std::shared_ptr<Physics3D> m_Physics;
};