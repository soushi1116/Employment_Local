#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

const float ATTACK_COLLISION_ACTIVE_TIME = 10.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 30.0f;

Knight::Knight(GameObject* owner) : CharacterMove(owner)
{

}

Knight::~Knight()
{

}

void Knight::Update()
{
	CharacterMove::Update();

	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();
	auto physicsPtr = m_Physics3D.lock();

	if (!parameterPtr || !animatorPtr || !physicsPtr) return;

	if (parameterPtr->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = parameterPtr->GetAttackCollision().lock();

		if (animatorPtr->GetNowTime() > ATTACK_COLLISION_ACTIVE_TIME)
		{
			VECTOR pos = physicsPtr->GetPos();
			VECTOR forward = physicsPtr->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			attackCollision->SetPosOffset(VScale(forward, 10.0f));
		}

		if (animatorPtr->GetNowTime() > ATTACK_COLLISION_INACTIVE_TIME)
		{
			attackCollision->SetActive(false);
			attackCollision->SetPosOffset(MyMath::VecZero());
		}
	}
}


void Knight::Attack()
{
	CharacterMove::Attack();
}

void Knight::Skill()
{
	CharacterMove::Skill();

	auto physicsPtr = m_Physics3D.lock();
	auto parameterPtr = m_Parameter.lock();

	if (!physicsPtr || !parameterPtr) return;
		
	EffectManager::GetInstance()->PlayEffect(EFFEKSEER_POWER_UP, m_Physics3D);

	CreateState(STATE_POWER_UP);

	
}

void Knight::SuperAttack()
{
	CharacterMove::SuperAttack();


}