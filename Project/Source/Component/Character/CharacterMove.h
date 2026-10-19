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
	void CollisionDamage(std::shared_ptr<DamageCollision> damageCollision);

	virtual void Attack();
	virtual void Skill();
	virtual void SuperAttack();

	void Damage(int damage);

protected:
	std::shared_ptr<Physics3D> m_Physics3D;
	std::shared_ptr<CharacterInput> m_Input;
	std::shared_ptr<CharacterParameter> m_Parameter;
	std::shared_ptr<Animator> m_Animator;
};