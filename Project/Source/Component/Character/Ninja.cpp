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

	if (parameterPtr->GetAction() == CharacterAction::ACTION_SUPER_ATTACK)
	{
		if (animatorPtr->GetNowTime() > SHURIKEN_THROW_TIME && m_ThrowFlg)
		{
			VECTOR thisPos = physicsPtr->GetPos();
			thisPos.y += SHURIKEN_HEIGHT_OFFSET;

			VECTOR forwardOffset = VScale(physicsPtr->GetForward(), SHURIKEN_FORWARD_OFFSET);

			VECTOR throwPos = VAdd(thisPos, forwardOffset);

			float dirAngleY = physicsPtr->GetDirAngleY();

			BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_SHURIKEN, throwPos, dirAngleY, parameterPtr->GetIndex());

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