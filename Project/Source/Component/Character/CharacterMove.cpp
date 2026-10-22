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
	m_Physics3D = m_Owner->GetComponent<Physics3D>();
	m_Parameter = m_Owner->GetComponent<CharacterParameter>();
	m_Animator = m_Owner->GetComponent<Animator>();
}

void CharacterMove::Step()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	float currentRotY = physicsPtr->GetRot().y;

	VECTOR frontVec = VGet(sinf(currentRotY), 0.0f, cosf(currentRotY));
	VECTOR rightVec = VGet(cosf(currentRotY), 0.0f, -sinf(currentRotY));

	VECTOR move = MyMath::VecZero();

	float stickX = (float)inputPtr->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	float stickY = (float)inputPtr->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	float rotYDelta = (float)inputPtr->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (animatorPtr->IsFinish())
	{
		parameterPtr->SetAction(CharacterAction::ACTION_NONE);
	}

	if (parameterPtr->GetAction() == CharacterAction::ACTION_NONE)
	{
		move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

		if (MyMath::VecLong(move) < 0.5f && MyMath::VecLong(move) > 0.0f)
		{
			parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_WALK);
		}
		else if (MyMath::VecLong(move) >= 0.5f)
		{
			parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_RUN);
		}
		else
		{
			parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_STOP);
		}
	}

	if (inputPtr->IsTriggerBattle(TRIGGER_ATTACK))
	{
		Attack();
		parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_ATTACK);
	}

	if (inputPtr->IsTriggerBattle(TRIGGER_SKILL))
	{
		Skill();
		parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_SKILL);
	}

	if (inputPtr->IsTriggerBattle(TRIGGER_SUPER_ATTACK))
	{
		SuperAttack();
		parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_SUPER_ATTACK);
	}

	if (parameterPtr->GetHp() <= 0)
	{
		Die();
	}

	physicsPtr->AddMove(move);
	physicsPtr->AddRot(rotYDelta);
}

void CharacterMove::Update()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	if (parameterPtr->IsChangeAnim())
	{
		animatorPtr->PlayAnim(parameterPtr->GetAnimType());

		parameterPtr->RenewAnim();
	}

	animatorPtr->UpdateAnim();
}

void CharacterMove::Draw()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	parameterPtr->GetAttackCollision().lock()->Draw();

	DrawFormatString(0, 700 + parameterPtr->GetIndex() * 100, COLOR_WHITE, "%f, %f,%f", physicsPtr->GetPos().x, physicsPtr->GetPos().y, physicsPtr->GetPos().z);
}

void CharacterMove::Attack()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	parameterPtr->SetAction(CharacterAction::ACTION_ATTACK);
}

void CharacterMove::Skill()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	parameterPtr->SetAction(CharacterAction::ACTION_SKILL);
}

void CharacterMove::SuperAttack()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	parameterPtr->SetAction(CharacterAction::ACTION_SUPER_ATTACK);
}

void CharacterMove::CollisionStage(int stageCollisionHandle)
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	VECTOR collisionPos = physicsPtr->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float collisionRadius = physicsPtr->GetCollision<SphereCollision>()->GetRadius();

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

	physicsPtr->AddPushBack(pushBackVec);

	physicsPtr->SetUseGravity(!onFloor);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterMove::CollisionCharacter(std::shared_ptr<Physics3D> characterPhysics)
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	VECTOR thisCollisionPos = physicsPtr->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float thisCollisionRadius = physicsPtr->GetCollision<SphereCollision>()->GetRadius();

	VECTOR thisRealPos = physicsPtr->GetPos();
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

		physicsPtr->AddPushBack(pushBackDir);
	}
}

void CharacterMove::CollisionDamage(std::shared_ptr<DamageCollision> damageCollision)
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	VECTOR thisCollisionPos = physicsPtr->GetCollision<SphereCollision>()->GetPos();
	float thisCollisionRadius = physicsPtr->GetCollision<SphereCollision>()->GetRadius();

	VECTOR damageCollisionPos = damageCollision->GetPos();
	float damageCollisionRadius = damageCollision->GetRadius();

	VECTOR thisToDamage = MyMath::VecCreate(thisCollisionPos, damageCollisionPos);
	thisToDamage.y = 0.0f;
	float distance = VSize(thisToDamage);
	float radiusSum = thisCollisionRadius + damageCollisionRadius;

	if (distance < radiusSum)
	{
		Damage(damageCollision->GetDamage());
		damageCollision->AddHitIndex(parameterPtr->GetIndex());
	}
}

void CharacterMove::Damage(int damage)
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	parameterPtr->DecreaseHP(damage);
}

void CharacterMove::Die()
{
	auto physicsPtr = m_Physics3D.lock();
	auto inputPtr = m_Input.lock();
	auto parameterPtr = m_Parameter.lock();
	auto animatorPtr = m_Animator.lock();

	if (!physicsPtr || !inputPtr || !parameterPtr || !animatorPtr) return;

	if (parameterPtr->GetAction() != CharacterAction::ACTION_DIE)
	{
		parameterPtr->SetAnim(CharacterAnimationType::ANIMATION_DIE);
		parameterPtr->SetAction(CharacterAction::ACTION_DIE);
	}

	// 仮のリスポーン処理
	parameterPtr->SetHp(parameterPtr->GetMaxHp());
}