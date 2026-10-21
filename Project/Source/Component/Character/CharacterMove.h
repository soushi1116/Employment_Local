#pragma once
#include "DxLib.h"
#include "../Component.h"
#include <memory>

class Physics3D;
class CharacterInput;
class CharacterParameter;
class Animator;
class DamageCollision;

class CharacterMove : public Component
{
public:
	CharacterMove(GameObject* owner);
	~CharacterMove();

	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;

	void CollisionStage(int stageCollisionHandle);
	void CollisionCharacter(std::shared_ptr<Physics3D> characterPhysics);
	void CollisionDamage(DamageCollision* damageCollision);

	virtual void Attack();
	virtual void Skill();
	virtual void SuperAttack();

	void Damage(int damage);
	void Die();

protected:
	Physics3D* m_Physics3D = nullptr;
	CharacterInput* m_Input = nullptr;
	CharacterParameter* m_Parameter = nullptr;
	Animator* m_Animator = nullptr;
};