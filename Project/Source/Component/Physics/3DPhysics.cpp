#include "3DPhysics.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "Collision/CollisionBase.h"
#include "../../MyColor/MyColor.h"

const float GRAVITY_ACCEL = 0.01f;

Physics3D::Physics3D(GameObject* owner) : Component(owner)
{
	m_Transform.m_Pos = MyMath::VecZero();
	m_Transform.m_Rot = MyMath::VecZero();
	m_Transform.m_Scale = MyMath::VecSame(1.0f);
	m_Transform.m_PrevPos = MyMath::VecZero();

	m_MoveInfo.m_Move = MyMath::VecZero();
	m_MoveInfo.m_DirAngleY = 0.0f;
	m_MoveInfo.m_Gravity = 0.0f;
	m_MoveInfo.m_UseGravity = false;

	m_CollInfo.m_PosOffset = MyMath::VecZero();
	m_CollInfo.m_ScaleOffset = MyMath::VecZero();
	m_CollInfo.m_CollisionPushBack = MyMath::VecZero();
}

Physics3D::~Physics3D()
{

}

void Physics3D::Start()
{
	VECTOR collPos = VAdd(m_Transform.m_Pos, m_CollInfo.m_PosOffset);
	VECTOR collScale = MyMath::VecScaleVector(m_Transform.m_Scale, m_CollInfo.m_ScaleOffset);

	if (m_CollInfo.m_Collision != nullptr)
	{
		m_CollInfo.m_Collision->SetPos(collPos);

		m_CollInfo.m_Collision->SetSize(collScale);
	}
}

void Physics3D::Step()
{
	m_CollInfo.m_CollisionPushBack = MyMath::VecZero();

	m_Transform.m_PrevPos = m_Transform.m_Pos;

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

void Physics3D::Update()
{
	m_Transform.m_Pos = VAdd(m_Transform.m_Pos, m_MoveInfo.m_Move);

	m_Owner->SetPos(m_Transform.m_Pos);
	m_Owner->SetScale(m_Transform.m_Scale);

	VECTOR collPos = VAdd(m_Transform.m_Pos, m_CollInfo.m_PosOffset);

	if (m_CollInfo.m_Collision != nullptr)
	{
		m_CollInfo.m_Collision->SetPos(collPos);
	}

	VECTOR moveDirNormal = MyMath::VecZero();

	if (!MyMath::IsVecZero(m_MoveInfo.m_Move))
	{
		moveDirNormal = VNorm(m_MoveInfo.m_Move);

		m_MoveInfo.m_DirAngleY = atan2f(moveDirNormal.x, moveDirNormal.z);
	}

	m_MoveInfo.m_Move = MyMath::VecZero();
}

void Physics3D::Draw()
{
	if (m_CollInfo.m_Collision != nullptr)
	{
		m_CollInfo.m_Collision->Draw();
	}
}

void Physics3D::SetCollision(CollisionBase* collision)
{
	m_CollInfo.m_Collision = collision;
}

void Physics3D::AddMove(VECTOR move)
{
	m_MoveInfo.m_Move = VAdd(m_MoveInfo.m_Move, move);
}

void Physics3D::AddRot(float rot)
{
	m_Transform.m_Rot.y += rot;
}