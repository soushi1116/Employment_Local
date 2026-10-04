#include "3DPhysics.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "../Transform.h"
#include "../Collision/CollisionBase.h"

const float GRAVITY_ACCEL = 0.01f;

_3DPhysics::_3DPhysics(GameObject* owner) : Component(owner)
{
	m_Transform.m_Pos = MyMath::VecZero();
	m_Transform.m_Rot = MyMath::VecZero();
	m_Transform.m_Scale = MyMath::VecSame(1.0f);

	m_MoveInfo.m_Move = MyMath::VecZero();
	m_MoveInfo.m_Gravity = 0.0f;
}

_3DPhysics::~_3DPhysics()
{

}

void _3DPhysics::Step()
{
	m_MoveInfo.m_Gravity += GRAVITY_ACCEL;

	m_MoveInfo.m_Move = MyMath::VecY(-m_MoveInfo.m_Gravity);
}

void _3DPhysics::Update()
{
	m_Transform.m_Pos = VAdd(m_Transform.m_Pos, m_MoveInfo.m_Move);
}

void _3DPhysics::SetCollision(CollisionBase* collision)
{
	m_Collision = collision;
}