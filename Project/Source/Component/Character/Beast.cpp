#include "Beast.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

const float ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 60.0f;

const float SUPER_ATTACK_COLLISION_ACTIVE_TIME = 50.0f;
const float SUPER_ATTACK_COLLISION_INACTIVE_TIME = 60.0f;

Beast::Beast(GameObject* owner) : CharacterMove(owner)
{
	m_SuperAttackModelPosOffset = 0.0f;
}

Beast::~Beast()
{

}

void Beast::Update()
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
		std::shared_ptr<DamageCollision> superAttackCollision = sharedPtrs.parameterShared->GetSuperAttackCollision().lock();

		VECTOR forward = sharedPtrs.physics3DShared->GetForward();
		VECTOR pos = sharedPtrs.physics3DShared->GetPos();

		sharedPtrs.physics3DShared->SetPos(VAdd(pos, VScale(forward, 0.3f)));

		if (nowAnimTime >= SUPER_ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < SUPER_ATTACK_COLLISION_INACTIVE_TIME)
		{
			superAttackCollision->SetActive(true);
			superAttackCollision->SetPos(pos);
		}

		if (nowAnimTime >= SUPER_ATTACK_COLLISION_INACTIVE_TIME)
		{
			superAttackCollision->SetActive(false);
			superAttackCollision->SetPosOffset(MyMath::VecZero());
		}

		auto model = m_Owner->GetComponent<ModelRenderer>();

		if (sharedPtrs.animatorShared->IsFinish())
		{
			model->SetPosOffset(MyMath::VecZero());
			m_SuperAttackModelPosOffset = 0.0f;
		}
		else
		{
			m_SuperAttackModelPosOffset -= 0.1f;
			model->SetPosOffset(VScale(forward, m_SuperAttackModelPosOffset));
		}
	}
}

void Beast::Attack()
{
	CharacterMove::Attack();	
}

void Beast::Skill()
{
	CharacterMove::Skill();

	EffectManager::GetInstance()->PlayEffect(EFFEKSEER_BOOST, m_Physics3D);

	CreateState(STATE_BOOST);
}

void Beast::SuperAttack()
{
	CharacterMove::SuperAttack();


}