#include "BulletParameter.h"
#include "../Component.h"
#include "../GameObject.h"

BulletParameter::BulletParameter(GameObject* owner) : Component(owner)
{
	m_Type = BULLET_TYPE_NONE;

	m_MoveSpeed = 0.0f;
}

BulletParameter::~BulletParameter()
{

}

void BulletParameter::Step()
{
	if (m_Physics != nullptr)
	{
		VECTOR forward = m_Physics->GetForward();

		m_Physics->AddMove(VScale(forward, m_MoveSpeed));
	}
}