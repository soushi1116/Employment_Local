#include "Fairy.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Managers/BulletManager/BulletManager.h"
#include "../../Managers//CharacterManager/CharacterManager.h"

const float LEAF_HEIGHT_OFFSET = 10.0f;
const float LEAF_FORWARD_OFFSET = 15.0f;
const float LEAF_THROW_TIME = 35.0f;

Fairy::Fairy(GameObject* owner) : CharacterMove(owner)
{
	m_ThrowFlg = false;
}

Fairy::~Fairy()
{

}

void Fairy::Update()
{
	CharacterMove::Update();

	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	if (sharedPtrs.animatorShared->GetNowTime() > LEAF_THROW_TIME && m_ThrowFlg)
	{
		VECTOR thisPos = sharedPtrs.physics3DShared->GetPos();
		thisPos.y += LEAF_HEIGHT_OFFSET;

		VECTOR forwardOffset = VScale(sharedPtrs.physics3DShared->GetForward(), LEAF_FORWARD_OFFSET);

		VECTOR throwPos = VAdd(thisPos, forwardOffset);

		float dirAngleY = sharedPtrs.physics3DShared->GetDirAngleY();

		if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_ATTACK)
		{
			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_NORMAL_LEAF, throwPos, dirAngleY, sharedPtrs.parameterShared->GetIndex());

			m_ThrowFlg = false;
		}
		else if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_SUPER_ATTACK)
		{
			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_POISON_LEAF, throwPos, dirAngleY, sharedPtrs.parameterShared->GetIndex());

			m_ThrowFlg = false;
		}
	}
}

void Fairy::Attack()
{
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
	CharacterMove::SuperAttack();

	m_ThrowFlg = true;
}