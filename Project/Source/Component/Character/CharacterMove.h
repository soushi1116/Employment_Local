#pragma once
#include "DxLib.h"
#include "../Component.h"
#include "CharacterState.h"
#include <memory>
#include "../../Managers/EffectManager/EffectManager.h"

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
	void CollisionItem(std::shared_ptr<GameObject> itemObj);

	virtual void Attack();
	virtual void Skill();
	virtual void SuperAttack();

	void Damage(int damage);
	void Die();
	void HPHeal(int amount);

	void CreateState(CharacterStateType type);
	void DeleteState();

	void ThrowActionDirOffset();

protected:
	struct SharedMembers
	{
		std::shared_ptr<Physics3D> physics3DShared;
		std::shared_ptr<CharacterInput> inputShared;
		std::shared_ptr<CharacterParameter> parameterShared;
		std::shared_ptr<Animator> animatorShared;
		bool isSafety = false;
	};

	std::weak_ptr<Physics3D> m_Physics3D;
	std::weak_ptr<CharacterInput> m_Input;
	std::weak_ptr<CharacterParameter> m_Parameter;
	std::weak_ptr<Animator> m_Animator;

	SharedMembers CheckMemberPtrs();
};