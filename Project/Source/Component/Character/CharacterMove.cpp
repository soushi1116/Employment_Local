#include "CharacterParameter.h"
#include "../Physics/Collision/DamageCollision.h"
#include "../CharacterInput/CharacterInput.h"
#include "CharacterMove.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "../../MyColor/MyColor.h"

const float GRAVITY_ACCEL = 0.01f;
const float CHARACTER_ROTATION_SPEED = 0.03f;

CharacterMove::CharacterMove(GameObject* owner) : Component(owner)
{
	
}

CharacterMove::~CharacterMove()
{
	
}

void CharacterMove::Start()
{
	m_Input = m_Owner->GetComponent<CharacterInput>();
	m_3DPhysics = m_Owner->GetComponent<_3DPhysics>();
	m_Parameter = m_Owner->GetComponent<CharacterParameter>();
	m_Animator = m_Owner->GetComponent<Animator>();
}

void CharacterMove::Step()
{
	float currentRotY = m_3DPhysics->GetRot().y;

	VECTOR frontVec = VGet(sinf(currentRotY), 0.0f, cosf(currentRotY));
	VECTOR rightVec = VGet(cosf(currentRotY), 0.0f, -sinf(currentRotY));

	float stickX = (float)m_Input->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	float stickY = (float)m_Input->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	VECTOR move = MyMath::VecZero();

	float rotYDelta = (float)m_Input->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (m_Animator->IsFinish())
	{
		if (m_Parameter->GetAction() == CharacterAction::ACTION_ATTACK)
		{
			std::shared_ptr<DamageCollision> attackCollision = m_Parameter->GetAttackCollision();
			attackCollision->SetActive(false);
			attackCollision->SetPosOffset(MyMath::VecZero());
		}

		m_Parameter->SetAction(CharacterAction::ACTION_NONE);
	}

	if (m_Parameter->GetAction() == CharacterAction::ACTION_NONE)
	{
		move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

		if (MyMath::VecLong(move) < 0.5f && MyMath::VecLong(move) > 0.0f)
		{
			m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_WALK);
		}
		else if (MyMath::VecLong(move) >= 0.5f)
		{
			m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_RUN);
		}
		else
		{
			m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_STOP);
		}
	}

	if (m_Input->IsTriggerBattle(TRIGGER_ATTACK))
	{
		Attack();
		m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_ATTACK);
	}

	if (m_Input->IsTriggerBattle(TRIGGER_SKILL))
	{
		Skill();
		m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_SKILL);
	}

	if (m_Input->IsTriggerBattle(TRIGGER_SUPER_ATTACK))
	{
		SuperAttack();
		m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_SUPER_ATTACK);
	}

	m_3DPhysics->AddMove(move);
	m_3DPhysics->AddRot(rotYDelta);
}

void CharacterMove::Update()
{
	if (m_Parameter->IsChangeAnim())
	{
		m_Animator->PlayAnim(m_Parameter->GetAnimType());

		m_Parameter->RenewAnim();
	}

	m_Animator->UpdateAnim();
}

void CharacterMove::Draw()
{
	m_Parameter->GetAttackCollision()->Draw();

	DrawFormatString(0, 700 + m_Parameter->GetIndex() * 100, COLOR_WHITE, "%d", m_Parameter->GetHp());
}

void CharacterMove::Attack()
{
	m_Parameter->SetAction(CharacterAction::ACTION_ATTACK);

	VECTOR pos = m_3DPhysics->GetPos();
	VECTOR forward = m_3DPhysics->GetForward();

	std::shared_ptr<DamageCollision> attackCollision = m_Parameter->GetAttackCollision();
	attackCollision->SetActive(true);
	attackCollision->SetPos(pos);
	attackCollision->SetPosOffset(VScale(forward, 10.0f));
}

void CharacterMove::Skill()
{
	m_Parameter->SetAction(CharacterAction::ACTION_SKILL);
}

void CharacterMove::SuperAttack()
{
	m_Parameter->SetAction(CharacterAction::ACTION_SUPER_ATTACK);
}

void CharacterMove::CollisionStage(int stageCollisionHandle)
{
	VECTOR collisionPos = m_3DPhysics->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float collisionRadius = m_3DPhysics->GetCollision<SphereCollision>()->GetRadius();

	VECTOR pushBackVec = MyMath::VecZero();

	bool onFloor = false;

	MV1_COLL_RESULT_POLY_DIM hitResult = MV1CollCheck_Sphere(stageCollisionHandle, -1, collisionPos, collisionRadius);

	for (int i = 0; i < hitResult.HitNum; i++)
	{
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];

		VECTOR centerToHitPos = MyMath::VecCreate(collisionPos, polygon.HitPosition);
		float distance = VSize(centerToHitPos);
		float pushBack = collisionRadius - distance;

		if (polygon.Normal.y > 0.1f)
		{
			float heightDiff = polygon.HitPosition.y - collisionPos.y;

			// 高さがあるものは無視
			if (heightDiff < -1.0f)
			{
				if (pushBack > pushBackVec.y)
				{
					pushBackVec.y = pushBack;
				}

				onFloor = true;
			}
		}
		else
		{
			pushBackVec = VScale(polygon.Normal, pushBack);
			
		}

		
	}

	m_3DPhysics->AddPushBack(pushBackVec);

	m_3DPhysics->SetUseGravity(!onFloor);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterMove::CollisionCharacter(std::shared_ptr<_3DPhysics> characterPhysics)
{
	VECTOR thisCollisionPos = m_3DPhysics->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float thisCollisionRadius = m_3DPhysics->GetCollision<SphereCollision>()->GetRadius();

	VECTOR thisRealPos = m_3DPhysics->GetPos();
	VECTOR pushedPos = thisRealPos;

	VECTOR targetCollisionPos = characterPhysics->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float targetCollisionRadius = characterPhysics->GetCollision<SphereCollision>()->GetRadius();

	VECTOR targetToThis = MyMath::VecCreate(targetCollisionPos, thisCollisionPos);
	targetToThis.y = 0.0f;
	float distance = VSize(targetToThis);
	float radiusSum = thisCollisionRadius + targetCollisionRadius;

	if (distance < radiusSum)
	{
		float pushBack = radiusSum - distance;
		VECTOR pushBackDir = VScale(VNorm(targetToThis), pushBack);

		m_3DPhysics->AddPushBack(pushBackDir);
	}
}

void CharacterMove::CollisionDamage(std::shared_ptr<DamageCollision> damageCollision)
{
	VECTOR thisCollisionPos = m_3DPhysics->GetCollision<SphereCollision>()->GetPos();
	float thisCollisionRadius = m_3DPhysics->GetCollision<SphereCollision>()->GetRadius();

	VECTOR damageCollisionPos = damageCollision->GetPos();
	float damageCollisionRadius = damageCollision->GetRadius();

	VECTOR thisToDamage = MyMath::VecCreate(thisCollisionPos, damageCollisionPos);
	float distance = VSize(thisToDamage);
	float radiusSum = thisCollisionRadius + damageCollisionRadius;

	if (distance > radiusSum)
	{
		Damage(damageCollision->GetDamage());
		damageCollision->AddHitIndex(m_Parameter->GetIndex());
	}
}

void CharacterMove::Damage(int damage)
{
	m_Parameter->DecreaseHP(damage);
}