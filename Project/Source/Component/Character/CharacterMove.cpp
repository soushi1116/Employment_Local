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
	CharacterAnimationType animType = CharacterAnimationType::ANIMATION_STOP;

	float currentRotY = m_3DPhysics->GetRot().y;

	VECTOR frontVec = VGet(sinf(currentRotY), 0.0f, cosf(currentRotY));
	VECTOR rightVec = VGet(cosf(currentRotY), 0.0f, -sinf(currentRotY));

	float stickX = (float)m_Input->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	float stickY = (float)m_Input->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	VECTOR move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

	float rotYDelta = (float)m_Input->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000.0f * CHARACTER_ROTATION_SPEED;

	if (MyMath::VecLong(move) < 0.5f && MyMath::VecLong(move) > 0.0f)
	{
		animType = CharacterAnimationType::ANIMATION_WALK;
	}
	else if (MyMath::VecLong(move) >= 0.5f)
	{
		animType = CharacterAnimationType::ANIMATION_RUN;
	}

	m_Parameter->SetAnim(animType);

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