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
	m_Input = m_Owner->GetComponent<CharacterInput>().get();
	m_Physics3D = m_Owner->GetComponent<Physics3D>().get();
	m_Parameter = m_Owner->GetComponent<CharacterParameter>().get();
	m_Animator = m_Owner->GetComponent<Animator>().get();
}

void CharacterMove::Step()
{
	float currentRotY = m_Physics3D->GetRot().y;

	VECTOR frontVec = VGet(sinf(currentRotY), 0.0f, cosf(currentRotY));
	VECTOR rightVec = VGet(cosf(currentRotY), 0.0f, -sinf(currentRotY));

	VECTOR move = MyMath::VecZero();

	float stickX = (float)m_Input->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	float stickY = (float)m_Input->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	float rotYDelta = (float)m_Input->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (m_Animator->IsFinish())
	{
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

	if (m_Parameter->GetHp() <= 0)
	{
		Die();
	}

	m_Physics3D->AddMove(move);
	m_Physics3D->AddRot(rotYDelta);
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
	VECTOR collisionPos = m_Physics3D->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float collisionRadius = m_Physics3D->GetCollision<SphereCollision>()->GetRadius();

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

	m_Physics3D->AddPushBack(pushBackVec);

	m_Physics3D->SetUseGravity(!onFloor);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterMove::CollisionCharacter(std::shared_ptr<Physics3D> characterPhysics)
{
	VECTOR thisCollisionPos = m_Physics3D->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float thisCollisionRadius = m_Physics3D->GetCollision<SphereCollision>()->GetRadius();

	VECTOR thisRealPos = m_Physics3D->GetPos();
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

		m_Physics3D->AddPushBack(pushBackDir);
	}
}

void CharacterMove::CollisionDamage(DamageCollision* damageCollision)
{
	VECTOR thisCollisionPos = m_Physics3D->GetCollision<SphereCollision>()->GetPos();
	float thisCollisionRadius = m_Physics3D->GetCollision<SphereCollision>()->GetRadius();

	VECTOR damageCollisionPos = damageCollision->GetPos();
	float damageCollisionRadius = damageCollision->GetRadius();

	VECTOR thisToDamage = MyMath::VecCreate(thisCollisionPos, damageCollisionPos);
	thisToDamage.y = 0.0f;
	float distance = VSize(thisToDamage);
	float radiusSum = thisCollisionRadius + damageCollisionRadius;

	if (distance < radiusSum)
	{
		Damage(damageCollision->GetDamage());
		damageCollision->AddHitIndex(m_Parameter->GetIndex());
	}
}

void CharacterMove::Damage(int damage)
{
	m_Parameter->DecreaseHP(damage);
}

void CharacterMove::Die()
{
	if (m_Parameter->GetAction() != CharacterAction::ACTION_DIE)
	{
		m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_DIE);
		m_Parameter->SetAction(CharacterAction::ACTION_DIE);
	}

	// 仮のリスポーン処理
	m_Parameter->SetHp(m_Parameter->GetMaxHp());
}