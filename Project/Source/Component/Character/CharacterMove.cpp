#include "../CharacterInput/CharacterInput.h"
#include "CharacterMove.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

const float GRAVITY_ACCEL = 0.01f;

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
}

void CharacterMove::Step()
{
	VECTOR move = MyMath::VecZero();
	move.x = (float)m_Input->GetInputBattle(INPUT_MOVE_X) / 1000.0f;
	move.z = (float)m_Input->GetInputBattle(INPUT_MOVE_Y) / 1000.0f;

	m_3DPhysics->AddMove(move);
}

void CharacterMove::Update()
{
	
}