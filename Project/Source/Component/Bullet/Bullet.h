#pragma once

#include "DxLib.h"
#include <memory>
#include "../Component.h"

class GameObject;
class Physics3D;
class DamageCollision;

class Bullet : public Component
{
public:
	Bullet(GameObject* owner);
	~Bullet();

public:
	void Step() override;

public:
	void SetType(BulletType type) { m_Type = type; }
	void SetSpeed(float speed) { m_MoveSpeed = speed; }
	void SetPhysics(std::weak_ptr<Physics3D> physics) { m_Physics = physics; }
	void SetLifeLimit(float time) { m_LifeLimit = time; }
	void SetDamageCollision(std::weak_ptr<DamageCollision> collision) { m_DamageCollision = collision; }

	BulletType GetType() const { return m_Type; }
	float GetSpeed() const { return m_MoveSpeed; }
	bool IsActive() const { return m_Active; }

private:
	BulletType m_Type;

	bool m_Active;

	float m_MoveSpeed;

	float m_LifeLimit;
	float m_LifeTimer;

	std::weak_ptr<Physics3D> m_Physics;

	std::weak_ptr<DamageCollision> m_DamageCollision;
};