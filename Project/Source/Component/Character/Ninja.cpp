#include "Ninja.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"
#include "../../Managers/BulletManager/BulletManager.h"
#include "../../Scene/SceneManager.h"

const float SHURIKEN_HEIGHT_OFFSET = 10.0f;
const float SHURIKEN_FORWARD_OFFSET = 15.0f;

Ninja::Ninja(GameObject* owner) : CharacterMove(owner)
{

}

Ninja::~Ninja()
{

}

void Ninja::Attack()
{
	CharacterMove::Attack();

	VECTOR pos = m_Physics3D->GetPos();
	VECTOR forward = m_Physics3D->GetForward();

	std::shared_ptr<DamageCollision> attackCollision = m_Parameter->GetAttackCollision();
	attackCollision->SetActive(true);
	attackCollision->SetPos(pos);
	attackCollision->SetPosOffset(VScale(forward, 10.0f));
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

	BulletManager::GetInstance()->CreateBullet(BULLET_TYPE_SHURIKEN, throwPos, m_Physics3D->GetForward());


}