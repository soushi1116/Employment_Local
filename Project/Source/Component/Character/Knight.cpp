#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Sound/SoundManager.h"

constexpr float ATTACK_COLLISION_ACTIVE_TIME = 10.0f;
constexpr float ATTACK_COLLISION_INACTIVE_TIME = 30.0f;
constexpr float ATTACK_SE_PLAY_TIME = 15.0f;

constexpr float SKILL_SE_PLAY_TIME = 5.0f;

constexpr float SUPER_ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
constexpr float SUPER_ATTACK_COLLISION_INACTIVE_TIME = 50.0f;
constexpr float SUPER_ATTACK_SE_PLAY_TIME = 10.0f;

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

	// 攻撃中
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = sharedPtrs.parameterShared->GetAttackCollision().lock();

		// ダメージコリジョン有効化
		if (nowAnimTime >= ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < ATTACK_COLLISION_INACTIVE_TIME)
		{
			VECTOR pos = sharedPtrs.physics3DShared->GetPos();
			VECTOR forward = sharedPtrs.physics3DShared->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			VECTOR posOffset = VAdd(VScale(forward, 10.0f), MyMath::VecY(10.0f));
			attackCollision->SetPosOffset(posOffset);
		}

		// ダメージコリジョン無効化
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

	// スキル中
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SKILL)
	{
		if (nowAnimTime >= SKILL_SE_PLAY_TIME && !sharedPtrs.parameterShared->IsActionSEPlayed())
		{
			SoundManager::GetInstance()->PlayCharacterSE(KNIGHT, ACTION_SKILL);
			sharedPtrs.parameterShared->SetActionSEPlayed(true);
		}
	}

	// 必殺技中
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SUPER_ATTACK)
	{
		std::shared_ptr<DamageCollision> attackCollision = sharedPtrs.parameterShared->GetAttackCollision().lock();

		// ダメージコリジョン有効化
		if (nowAnimTime >= SUPER_ATTACK_COLLISION_ACTIVE_TIME && nowAnimTime < SUPER_ATTACK_COLLISION_INACTIVE_TIME)
		{
			VECTOR pos = sharedPtrs.physics3DShared->GetPos();
			VECTOR forward = sharedPtrs.physics3DShared->GetForward();

			attackCollision->SetActive(true);
			attackCollision->SetPos(pos);
			attackCollision->SetPosOffset(VScale(forward, 10.0f));
			attackCollision->SetPosOffset(MyMath::VecY(10.0f));
		}

		// ダメージコリジョン無効化
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