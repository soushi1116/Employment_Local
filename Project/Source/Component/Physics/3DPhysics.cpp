#include "3DPhysics.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"
#include "Collision/CollisionBase.h"
#include "../../MyColor/MyColor.h"

constexpr float GRAVITY_ACCEL = 0.01f;

Physics3D::Physics3D(GameObject* owner) 
	: Component(owner)
	, m_Transform{ MyMath::VecZero(), MyMath::VecZero(), MyMath::VecSame(1.0f), MyMath::VecZero()}
	, m_MoveInfo{ MyMath::VecZero(), 0.0f, 0.0f, false }
	, m_CollInfo{ {}, MyMath::VecZero(), MyMath::VecSame(1.0f), MyMath::VecZero()}
{

}

Physics3D::~Physics3D()
{

}

void Physics3D::Start()
{
	if (auto collisionPtr = m_CollInfo.m_Collision.lock())
	{
		VECTOR collPos = VAdd(m_Transform.m_Pos, m_CollInfo.m_PosOffset);
		VECTOR collScale = MyMath::VecScaleVector(m_Transform.m_Scale, m_CollInfo.m_ScaleOffset);

		collisionPtr->SetPos(collPos);

		collisionPtr->SetSize(collScale);
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

	m_MoveInfo.m_Move = VAdd(m_MoveInfo.m_Move, MyMath::VecY(-m_MoveInfo.m_Gravity));
}

void Physics3D::Update()
{
	m_Transform.m_Pos = VAdd(m_Transform.m_Pos, m_MoveInfo.m_Move);

	m_Owner->SetPos(m_Transform.m_Pos);
	m_Owner->SetScale(m_Transform.m_Scale);

	VECTOR collPos = VAdd(m_Transform.m_Pos, m_CollInfo.m_PosOffset);

	if (auto collisionPtr = m_CollInfo.m_Collision.lock())
	{
		collisionPtr->SetPos(collPos);
	}

	VECTOR moveDirNormal = MyMath::VecZero();

	if (!MyMath::IsVecZero(m_MoveInfo.m_Move))
	{
		moveDirNormal = VNorm(m_MoveInfo.m_Move);

		if (moveDirNormal.x != 0.0f && moveDirNormal.z != 0.0f)
		{
			// キャラクターの場合アクション中でないときのみ向き補正
			if (auto characterParam = m_Owner->GetComponent<CharacterParameter>())
			{
				if (characterParam->ActionAble())
				{
					m_MoveInfo.m_DirAngleY = atan2f(moveDirNormal.x, moveDirNormal.z);
				}
			}
			else
			{
				m_MoveInfo.m_DirAngleY = atan2f(moveDirNormal.x, moveDirNormal.z);
			}
		}
	}

	m_MoveInfo.m_Move = MyMath::VecZero();
}

void Physics3D::Draw()
{
	if (auto collisionPtr = m_CollInfo.m_Collision.lock())
	{
		collisionPtr->Draw();
	}
}

void Physics3D::SetCollision(std::weak_ptr<CollisionBase> collision)
{
	m_CollInfo.m_Collision = collision;
}

void Physics3D::AddMove(VECTOR move)
{
	m_MoveInfo.m_Move = VAdd(m_MoveInfo.m_Move, move);

	if (m_Owner->CompareTag(TAG_ARROW))
	{
		int dummy = 0; // ★ここにブレークポイントを置く
	}
}

void Physics3D::AddRot(float rot)
{
	m_Transform.m_Rot.y += rot;
}