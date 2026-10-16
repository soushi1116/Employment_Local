#pragma once
#include "DxLib.h"
#include "../Component.h"

class _3DPhysics;
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
	void CollisionCharacter(std::shared_ptr<_3DPhysics> characterPhysics);
	void CollisionDamage(std::shared_ptr<DamageCollision> damageCollision);

	void Attack();
	void Skill();
	void SuperAttack();

	void Damage(int damage);

private:
	std::shared_ptr<_3DPhysics> m_3DPhysics;
	std::shared_ptr<CharacterInput> m_Input;
	std::shared_ptr<CharacterParameter> m_Parameter;
	std::shared_ptr<Animator> m_Animator;
};