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

const float ATTACK_COLLISION_ACTIVE_TIME = 30.0f;
const float ATTACK_COLLISION_INACTIVE_TIME = 60.0f;

Ninja::Ninja(GameObject* owner) : CharacterMove(owner)
{

}

Ninja::~Ninja()
{

}

void Ninja::Update()
{
	CharacterMove::Update();

	if (m_Parameter->GetAction() == CharacterAction::ACTION_ATTACK)
	{
		DamageCollision* attackCollision = m_Parameter->GetAttackCollision();

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

void Ninja::Attack()
{
	CharacterMove::Attack();
}

void Ninja::Skill()
{
	CharacterMove::Skill();


}

void Ninja::SuperAttack()
{
	CharacterMove::SuperAttack();

	VECTOR thisPos = m_Physics3D->GetPos();
	thisPos.y += SHURIKEN_HEIGHT_OFFSET;
	
	VECTOR forwardOffset = VScale(m_Physics3D->GetForward(), SHURIKEN_FORWARD_OFFSET);

	VECTOR throwPos = VAdd(thisPos, forwardOffset);

	float dirAngleY = m_Physics3D->GetDirAngleY();

	BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_SHURIKEN, throwPos, dirAngleY, m_Parameter->GetIndex());


}