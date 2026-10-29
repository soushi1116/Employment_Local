#include "Ninja.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Managers/BulletManager/BulletManager.h"
#include "../../Scene/SceneManager.h"
#include "../Bullet/Bullet.h"

const float SHURIKEN_HEIGHT_OFFSET = 10.0f;
const float SHURIKEN_FORWARD_OFFSET = 15.0f;
const float SHURIKEN_THROW_TIME = 35.0f;

const float ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 60.0f;

Ninja::Ninja(GameObject* owner) : CharacterMove(owner)
{
	m_ThrowFlg = false;
}

Ninja::~Ninja()
{

}

void Ninja::Update()
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
		if (nowAnimTime >= SHURIKEN_THROW_TIME && m_ThrowFlg)
		{
			VECTOR thisPos = sharedPtrs.physics3DShared->GetPos();
			thisPos.y += SHURIKEN_HEIGHT_OFFSET;

			VECTOR forwardOffset = VScale(sharedPtrs.physics3DShared->GetForward(), SHURIKEN_FORWARD_OFFSET);

			VECTOR throwPos = VAdd(thisPos, forwardOffset);

			float dirAngleY = sharedPtrs.physics3DShared->GetDirAngleY();

			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_SHURIKEN, throwPos, dirAngleY, sharedPtrs.parameterShared->GetIndex());

			m_ThrowFlg = false;
		}
	}
}

void Ninja::Attack()
{
	CharacterMove::Attack();
}

void Ninja::Skill()
{
	CharacterMove::Skill();

	CreateState(STATE_INVISIBLE);
}

void Ninja::SuperAttack()
{
	CharacterMove::SuperAttack();

	m_ThrowFlg = true;
}