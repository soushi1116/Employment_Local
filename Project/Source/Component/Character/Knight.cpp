#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Sound/SoundManager.h"

const float ATTACK_COLLISION_ACTIVE_TIME = 10.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 30.0f;
const float ATTACK_SE_PLAY_TIME = 15.0f;

const float SKILL_SE_PLAY_TIME = 5.0f;

const float SUPER_ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float SUPER_ATTACK_COLLISION_INACTIVE_TIME = 50.0f;
const float SUPER_ATTACK_SE_PLAY_TIME = 10.0f;

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

	// UŒ‚’†
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = sharedPtrs.parameterShared->GetAttackCollision().lock();

		if (nowAnimTime >= ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < ATTACK_COLLISION_INACTIVE_TIME)
		{
			VECTOR pos = sharedPtrs.physics3DShared->GetPos();
			VECTOR forward = sharedPtrs.physics3DShared->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			VECTOR posOffset = VAdd(VScale(forward, 10.0f), MyMath::VecY(10.0f));
			attackCollision->SetPosOffset(posOffset);
		}

		if (nowAnimTime >= ATTACK_COLLISION_INACTIVE_TIME)
		{
			attackCollision->SetActive(false);
			attackCollision->SetPosOffset(MyMath::VecZero());
		}

		if (nowAnimTime >= ATTACK_SE_PLAY_TIME && !sharedPtrs.parameterShared->IsActionSEPlayed())
		{
			SoundManager::GetInstance()->PlayCharacterSE(KNIGHT, ACTION_ATTACK);
			sharedPtrs.parameterShared->SetActionSEPlayed(true);
		}
	}

	// ƒXƒLƒ‹’†
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SKILL)
	{
		if (nowAnimTime >= SKILL_SE_PLAY_TIME && !sharedPtrs.parameterShared->IsActionSEPlayed())
		{
			SoundManager::GetInstance()->PlayCharacterSE(KNIGHT, ACTION_SKILL);
			sharedPtrs.parameterShared->SetActionSEPlayed(true);
		}
	}

	// •KŽE‹Z’†
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
			attackCollision->SetPosOffset(MyMath::VecY(10.0f));
		}

		if (nowAnimTime >= SUPER_ATTACK_COLLISION_INACTIVE_TIME)
		{
			attackCollision->SetActive(false);
			attackCollision->SetPosOffset(MyMath::VecZero());
		}

		if (nowAnimTime >= SUPER_ATTACK_SE_PLAY_TIME && !sharedPtrs.parameterShared->IsActionSEPlayed())
		{
			SoundManager::GetInstance()->PlayCharacterSE(KNIGHT, ACTION_SUPER_ATTACK);
			sharedPtrs.parameterShared->SetActionSEPlayed(true);
		}
	}
}


void Knight::Attack()
{
	CharacterMove::Attack();

	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();
}

void Knight::Skill()
{
	CharacterMove::Skill();

	CreateState(STATE_POWER_UP);
}

void Knight::SuperAttack()
{
	CharacterMove::SuperAttack();

	CreateState(STATE_BOOST);
}