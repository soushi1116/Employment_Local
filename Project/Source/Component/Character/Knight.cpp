#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

const float ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 60.0f;

Knight::Knight(GameObject* owner) : CharacterMove(owner)
{

}

Knight::~Knight()
{

}

void Knight::Update()
{
	CharacterMove::Update();

	if (m_Parameter->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = m_Parameter->GetAttackCollision();

		if (m_Animator->GetNowTime() > ATTACK_COLLISION_ACTIVE_TIME)
		{
			VECTOR pos = m_Physics3D->GetPos();
			VECTOR forward = m_Physics3D->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			attackCollision->SetPosOffset(VScale(forward, 10.0f));
		}

		if (m_Animator->GetNowTime() > ATTACK_COLLISION_INACTIVE_TIME)
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


}

void Knight::SuperAttack()
{
	CharacterMove::SuperAttack();


}