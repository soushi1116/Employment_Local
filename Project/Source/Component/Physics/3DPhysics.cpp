#include "3DPhysics.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "Collision/CollisionBase.h"

const float GRAVITY_ACCEL = 0.01f;

_3DPhysics::_3DPhysics(GameObject* owner) : Component(owner)
{
	m_Transform.m_Pos = MyMath::VecZero();
	m_Transform.m_Rot = MyMath::VecZero();
	m_Transform.m_Scale = MyMath::VecSame(1.0f);

	m_MoveInfo.m_Move = MyMath::VecZero();
	m_MoveInfo.m_Gravity = 0.0f;
	m_MoveInfo.m_UseGravity = false;

	m_CollInfo.m_Collision = nullptr;
	m_CollInfo.m_PosOffset = MyMath::VecZero();
	m_CollInfo.m_ScaleOffset = MyMath::VecZero();
}

_3DPhysics::~_3DPhysics()
{

}

void _3DPhysics::Step()
{
	

	if (m_MoveInfo.m_UseGravity)
	{
		m_MoveInfo.m_Gravity += GRAVITY_ACCEL;
	}
	else
	{
		m_MoveInfo.m_Gravity = 0.0f;
	}

	m_MoveInfo.m_Move = MyMath::VecY(-m_MoveInfo.m_Gravity);
}

void _3DPhysics::AddMove(VECTOR move)
{
	m_MoveInfo.m_Move = VAdd(m_MoveInfo.m_Move, move);
}

void _3DPhysics::Update()
{
	m_Transform.m_Pos = VAdd(m_Transform.m_Pos, m_MoveInfo.m_Move);

	m_Owner->SetPos(m_Transform.m_Pos);
	m_Owner->SetScale(m_Transform.m_Scale);

	VECTOR collPos = VAdd(m_Transform.m_Pos, m_CollInfo.m_PosOffset);
	VECTOR collScale = MyMath::VecScaleVector(m_Transform.m_Scale, m_CollInfo.m_ScaleOffset);

	if (m_CollInfo.m_Collision != nullptr)
	{
		m_CollInfo.m_Collision->SetPos(collPos);

		m_CollInfo.m_Collision->SetSize(collScale);
	}

	m_MoveInfo.m_Move = MyMath::VecZero();
}

void _3DPhysics::Draw()
{
	if (m_CollInfo.m_Collision != nullptr)
	{
		m_CollInfo.m_Collision->Draw();
	}
}

void _3DPhysics::SetCollision(CollisionBase* collision)
{
	m_CollInfo.m_Collision = collision;
}

void _3DPhysics::HitFloor()
{
	m_MoveInfo.m_UseGravity = false;
}