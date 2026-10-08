#include "../CharacterInput/CharacterInput.h"
#include "CharacterMove.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "CharacterParameter.h"

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

	VECTOR move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

	float rotYDelta = (float)m_Input->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (m_Animator->IsFinish())
	{
		m_Parameter->SetAction(CharacterAction::ACTION_NONE);
	}

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
		if (m_Parameter->GetAction() == CharacterAction::ACTION_NONE)
		{
			m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_STOP);
		}
	}

	if (m_Input->IsTriggerBattle(TRIGGER_ATTACK))
	{
		Attack();
		m_Parameter->SetAnim(CharacterAnimationType::ANIMATION_ATTACK);
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

void CharacterMove::Attack()
{
	m_Parameter->SetAction(CharacterAction::ACTION_ATTACK);
}

void CharacterMove::StageCollision(int stageCollisionHandle)
{
	VECTOR collisionPos = m_3DPhysics->GetCollison<SphereCollision>()->GetPos(); // コリジョンの位置
	float collisionRadius = m_3DPhysics->GetCollison<SphereCollision>()->GetRadius();

	VECTOR realPos = m_3DPhysics->GetPos(); // 実際のキャラクターの位置
	VECTOR pushedPos = realPos; // 押し出し後の位置

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
				pushedPos.y += pushBack;
				onFloor = true;
			}
		}
		else
		{
			VECTOR pushBackDir = VScale(polygon.Normal, pushBack);
			pushedPos.x += pushBackDir.x;
			pushedPos.z += pushBackDir.z;
		}
	}

	m_3DPhysics->SetUseGravity(!onFloor);
	m_3DPhysics->SetPos(pushedPos);

	MV1CollResultPolyDimTerminate(hitResult);
}