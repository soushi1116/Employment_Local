#include "Fairy.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Managers/BulletManager/BulletManager.h"
#include "../../Managers//CharacterManager/CharacterManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Sound/SoundManager.h"

const float LEAF_HEIGHT_OFFSET = 10.0f;
const float LEAF_FORWARD_OFFSET = 15.0f;

const float LEAF_THROW_TIME = 35.0f;

const float SKILL_SE_PLAY_TIME = 15.0f;

Fairy::Fairy(GameObject* owner)
	: CharacterMove (owner)
	, m_ThrowFlg (false)
{

}

Fairy::~Fairy()
{

}

void Fairy::Update()
{
	CharacterMove::Update();

	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	float nowAnimTime = sharedPtrs.animatorShared->GetNowTime();

	if (nowAnimTime > LEAF_THROW_TIME && m_ThrowFlg)
	{
		VECTOR thisPos = sharedPtrs.physics3DShared->GetPos();
		thisPos.y += LEAF_HEIGHT_OFFSET;

		VECTOR forwardOffset = VScale(sharedPtrs.physics3DShared->GetForward(), LEAF_FORWARD_OFFSET);

		VECTOR throwPos = VAdd(thisPos, forwardOffset);

		float dirAngleY = sharedPtrs.physics3DShared->GetDirAngleY();

		// UŒ‚’†
		if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_ATTACK)
		{
			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_NORMAL_LEAF, throwPos, dirAngleY, sharedPtrs.parameterShared->GetIndex());

			if (!sharedPtrs.parameterShared->IsActionSEPlayed())
			{
				SoundManager::GetInstance()->PlayCharacterSE(FAIRY, ACTION_SUPER_ATTACK);
				sharedPtrs.parameterShared->SetActionSEPlayed(true);
			}

			m_ThrowFlg = false;
		}

		// •KŽE‹Z’†
		if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SUPER_ATTACK)
		{
			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_POISON_LEAF, throwPos, dirAngleY, sharedPtrs.parameterShared->GetIndex());

			if (!sharedPtrs.parameterShared->IsActionSEPlayed())
			{
				SoundManager::GetInstance()->PlayCharacterSE(FAIRY, ACTION_SUPER_ATTACK);
				sharedPtrs.parameterShared->SetActionSEPlayed(true);
			}

			m_ThrowFlg = false;
		}
	}

	// ƒXƒLƒ‹’†
	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SKILL)
	{
		if (nowAnimTime >= SKILL_SE_PLAY_TIME && !sharedPtrs.parameterShared->IsActionSEPlayed())
		{
			SoundManager::GetInstance()->PlayCharacterSE(FAIRY, ACTION_SKILL);
			sharedPtrs.parameterShared->SetActionSEPlayed(true);
		}
	}
}

void Fairy::Attack()
{
	ThrowActionDirOffset();

	CharacterMove::Attack();

	m_ThrowFlg = true;
}

void Fairy::Skill()
{
	CharacterMove::Skill();

	auto characters = CharacterManager::GetInstance()->GetCharacters();

	for (auto& character : characters)
	{
		auto characterObj = character.lock();

		if (!characterObj) continue;

		auto characterMove = characterObj->GetComponent<CharacterMove>();
		auto characterParameter = characterObj->GetComponent<CharacterParameter>();

		if (characterParameter->IsBoss()) continue;

		characterMove->HPHeal(20);
	}
}

void Fairy::SuperAttack()
{
	ThrowActionDirOffset();

	CharacterMove::SuperAttack();

	m_ThrowFlg = true;
}