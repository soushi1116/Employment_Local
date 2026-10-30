#include "CharacterParameter.h"
#include "../Physics/Collision/DamageCollision.h"
#include "../CharacterInput/CharacterInput.h"
#include "CharacterMove.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "../../MyColor/MyColor.h"
#include "../../Scene/SceneManager.h"

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
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	float currentRotY = sharedPtrs.physics3DShared->GetRot().y;

	VECTOR frontVec = VGet(sinf(currentRotY), 0.0f, cosf(currentRotY));
	VECTOR rightVec = VGet(cosf(currentRotY), 0.0f, -sinf(currentRotY));

	VECTOR move = MyMath::VecZero();

	float stickX = (float)sharedPtrs.inputShared->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	float stickY = (float)sharedPtrs.inputShared->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	float rotYDelta = (float)sharedPtrs.inputShared->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (sharedPtrs.animatorShared->IsFinish())
	{
		sharedPtrs.parameterShared->SetAction(CharacterAction::ACTION_NONE);
	}

	if (sharedPtrs.parameterShared->GetAction() == CharacterAction::ACTION_NONE)
	{
		move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

		move = VScale(move, sharedPtrs.parameterShared->GetSpeed());

		if (MyMath::VecLong(move) < 0.5f && MyMath::VecLong(move) > 0.0f)
		{
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_WALK);
		}
		else if (MyMath::VecLong(move) >= 0.5f)
		{
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_RUN);
		}
		else
		{
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_STOP);
		}
	}

	if (sharedPtrs.parameterShared->ActionAble())
	{
		if (sharedPtrs.inputShared->IsTriggerBattle(TRIGGER_ATTACK))
		{
			Attack();
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_ATTACK);
		}

		if (sharedPtrs.inputShared->IsTriggerBattle(TRIGGER_SKILL))
		{
			Skill();
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_SKILL);
		}

		if (sharedPtrs.inputShared->IsTriggerBattle(TRIGGER_SUPER_ATTACK))
		{
			SuperAttack();
			sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_SUPER_ATTACK);
		}
	}

	if (sharedPtrs.parameterShared->GetHp() <= 0)
	{
		Die();
	}

	sharedPtrs.physics3DShared->AddMove(move);
	sharedPtrs.physics3DShared->AddRot(rotYDelta);
}

void CharacterMove::Update()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	if (sharedPtrs.parameterShared->IsChangeAnim())
	{
		sharedPtrs.animatorShared->PlayAnim(sharedPtrs.parameterShared->GetAnimType());

		sharedPtrs.parameterShared->RenewAnim();
	}

	sharedPtrs.animatorShared->UpdateAnim();

	auto states = sharedPtrs.parameterShared->GetStates();

	if (!states.empty())
	{
		bool isOverInterval = false;

		std::shared_ptr<Timer> timer;

		for (auto& state : states)
		{
			auto stateObj = state.lock();

			if (!stateObj) continue;

			timer = stateObj->GetComponent<Timer>();

			auto statePtr = stateObj->GetComponent<CharacterState>();

			if (statePtr->GetType() == STATE_INVISIBLE)
			{
				auto modelCmp = m_Owner->GetComponent<ModelRenderer>();

				if (modelCmp != nullptr)
				{
					modelCmp->SetOpacity(0.5f);
				}
				continue;
			}

			if (timer->IsOverInterval())
			{
				CharacterStateType type = statePtr->GetType();
				EffekseerEffectType effectType = EFFEKSEER_EFFECT_TYPE_NONE;

				switch (type)
				{
				case STATE_POWER_UP:
					effectType = EFFEKSEER_POWER_UP_STATE;
					break;
				case STATE_DEFFENCE_UP:
					effectType = EFFEKSEER_DEFENCE_UP_STATE;
					break;
				case STATE_BOOST:
					effectType = EFFEKSEER_BOOST_STATE;
					break;
				case STATE_POISONED:
					effectType = EFFEKSEER_POISON_STATE;
					break;
				case STATE_TYPE_MAX:
					break;
				case STATE_TYPE_NONE:
					break;
				default:
					break;
				}

				if (effectType == EFFEKSEER_EFFECT_TYPE_NONE) continue;

				EffectManager::GetInstance()->PlayEffect(effectType, m_Physics3D);
				timer->SetIsOverInterval(false);
			}
		}
	}

	DeleteState();
}

void CharacterMove::Draw()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->GetAttackCollision().lock()->Draw();	
}

void CharacterMove::Attack()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->SetAction(CharacterAction::ACTION_ATTACK);
}

void CharacterMove::Skill()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->SetAction(CharacterAction::ACTION_SKILL);
}

void CharacterMove::SuperAttack()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->SetAction(CharacterAction::ACTION_SUPER_ATTACK);
}

void CharacterMove::CollisionStage(int stageCollisionHandle)
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	VECTOR collisionPos = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float collisionRadius = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetRadius();

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
			sharedPtrs.physics3DShared->AddPushBack(pushBackVec);
		}
	}

	

	sharedPtrs.physics3DShared->SetUseGravity(!onFloor);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterMove::CollisionCharacter(std::shared_ptr<Physics3D> characterPhysics)
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	VECTOR thisCollisionPos = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetPos(); // コリジョンの位置
	float thisCollisionRadius = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetRadius();

	VECTOR thisRealPos = sharedPtrs.physics3DShared->GetPos();
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

		sharedPtrs.physics3DShared->AddPushBack(pushBackDir);
	}
}

void CharacterMove::CollisionDamage(std::shared_ptr<DamageCollision> damageCollision)
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	VECTOR thisCollisionPos = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetPos();
	float thisCollisionRadius = sharedPtrs.physics3DShared->GetCollision<SphereCollision>()->GetRadius();

	VECTOR damageCollisionPos = damageCollision->GetPos();
	float damageCollisionRadius = damageCollision->GetRadius();

	VECTOR thisToDamage = MyMath::VecCreate(thisCollisionPos, damageCollisionPos);
	thisToDamage.y = 0.0f;
	float distance = VSize(thisToDamage);
	float radiusSum = thisCollisionRadius + damageCollisionRadius;

	if (distance < radiusSum)
	{
		Damage(damageCollision->GetDamage());
		damageCollision->AddHitIndex(sharedPtrs.parameterShared->GetIndex());
	}
}

void CharacterMove::Damage(int damage)
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->DecreaseHP(damage);
}

void CharacterMove::HPHeal(int amount)
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	sharedPtrs.parameterShared->IncreaseHP(amount);

	EffectManager::GetInstance()->PlayEffect(EFFEKSEER_HP_HEAL, m_Physics3D);
}

void CharacterMove::Die()
{
	CharacterMove::SharedMembers sharedPtrs = CheckMemberPtrs();

	if (!sharedPtrs.isSafety) return;

	if (sharedPtrs.parameterShared->GetAction() != CharacterAction::ACTION_DIE)
	{
		sharedPtrs.parameterShared->SetAnim(CharacterAnimationType::ANIMATION_DIE);
		sharedPtrs.parameterShared->SetAction(CharacterAction::ACTION_DIE);
	}

	// 仮のリスポーン処理
	sharedPtrs.parameterShared->SetHp(sharedPtrs.parameterShared->GetMaxHp());
}

void CharacterMove::CreateState(CharacterStateType type)
{
	if (auto parameterPtr = m_Parameter.lock())
	{
		auto stateObj = std::make_shared<GameObject>();

		std::shared_ptr<CharacterState> newState = stateObj->AddComponent<CharacterState>();

		newState->SetType(type);
		newState->SetActive(true);

		std::shared_ptr<Timer> newTimer = stateObj->AddComponent<Timer>();
		newState->SetTimer(newTimer);
		newTimer->CountStart(10.0f);
		newTimer->SetInterval(3.0f);

		parameterPtr->AddState(stateObj);

		SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();
		nowScene->Instantiate(stateObj);
	}
}

void CharacterMove::DeleteState()
{
	auto parameterPtr = m_Parameter.lock();

	if (!parameterPtr) return;

	auto& states = parameterPtr->GetStates();

	if (states.empty()) return;

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	states.erase(
		std::remove_if(states.begin(), states.end(),
			[](const auto& state)
			{
				auto statePtr = state.lock();

				if (!statePtr) return true;

				std::shared_ptr <CharacterState> stateCmp = statePtr->GetComponent<CharacterState>();

				if (!stateCmp) return true;

				if (!stateCmp->IsActive())
				{
					statePtr->SetActive(false);
					return true;
				}

				return false;
			}),
		states.end()
	);
}

CharacterMove::SharedMembers CharacterMove::CheckMemberPtrs()
{
	CharacterMove::SharedMembers ptrs;

	ptrs.animatorShared = m_Animator.lock();
	ptrs.inputShared = m_Input.lock();
	ptrs.parameterShared = m_Parameter.lock();
	ptrs.physics3DShared = m_Physics3D.lock();

	if (!ptrs.animatorShared || !ptrs.inputShared || !ptrs.parameterShared || !ptrs.physics3DShared)
	{
		ptrs.isSafety = false;
	}
	else
	{
		ptrs.isSafety = true;
	}

	return ptrs;
}
