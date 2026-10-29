#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

const float ATTACK_COLLISION_ACTIVE_TIME = 10.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 30.0f;

const float SUPER_ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float SUPER_ATTACK_COLLISION_INACTIVE_TIME = 50.0f;

Knight::Knight(GameObject* owner) : CharacterMove(owner)
{

}

Knight::~Knight()
{

}

void Knight::Update()
{
	CharacterMove::Update();

	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	float nowAnimTime = sharedPtrs.animatorShared->GetNowTime();

	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = sharedPtrs.parameterShared->GetAttackCollision().lock();

		if (nowAnimTime >= ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < ATTACK_COLLISION_INACTIVE_TIME)
		{
			VECTOR pos = sharedPtrs.physics3DShared->GetPos();
			VECTOR forward = sharedPtrs.physics3DShared->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			attackCollision->SetPosOffset(VScale(forward, 10.0f));
		}

		if (nowAnimTime >= ATTACK_COLLISION_INACTIVE_TIME)
		{
			attackCollision->SetActive(false);
			attackCollision->SetPosOffset(MyMath::VecZero());
		}
	}

	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SUPER_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = sharedPtrs.parameterShared->GetAttackCollision().lock();

		if (nowAnimTime >= SUPER_ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < SUPER_ATTACK_COLLISION_INACTIVE_TIME)
		{
			VECTOR pos = sharedPtrs.physics3DShared->GetPos();
			VECTOR forward = sharedPtrs.physics3DShared->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			attackCollision->SetPosOffset(VScale(forward, 10.0f));
		}

		if (nowAnimTime >= SUPER_ATTACK_COLLISION_INACTIVE_TIME)
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
		
	EffectManager::GetInstance()->PlayEffect(EFFEKSEER_POWER_UP, m_Physics3D);

	CreateState(STATE_POWER_UP);
}

void Knight::SuperAttack()
{
	CharacterMove::SuperAttack();

	EffectManager::GetInstance()->PlayEffect(EFFEKSEER_BOOST, m_Physics3D);

	CreateState(STATE_BOOST);
}