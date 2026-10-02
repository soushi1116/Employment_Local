#include "CharacterMove.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "../Transform.h"

const float GRAVITY_ACCEL = 0.01f;

CharacterMove::CharacterMove(GameObject* owner) : Component(owner)
{
	m_Move = MyMath::VecZero();
	m_Gravity = 0.0f;
}

CharacterMove::~CharacterMove()
{
	
}

void CharacterMove::Step()
{
	m_Gravity += GRAVITY_ACCEL;

	m_Move = MyMath::VecY(-m_Gravity);
}

void CharacterMove::Update()
{
	VECTOR currentPos = m_Owner->GetComponent<Transform>()->GetPos();
	VECTOR nextPos = VAdd(currentPos, m_Move);
	//m_Owner->GetComponent<Transform>()->SetPos(nextPos);
	
}