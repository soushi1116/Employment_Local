#pragma once

#include "DxLib.h"
#include "../Component.h"
#include <memory>
#include "../../MyMath/MyMath.h"

class CollisionBase;

class Physics3D : public Component
{
public:
	Physics3D(GameObject* owner);
	~Physics3D();

	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;

	GameObject* GetOwner() { return m_Owner; }

	void SetPos(VECTOR pos) { m_Transform.m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Transform.m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Transform.m_Scale = scale; }
	void SetUseGravity(bool useGravity) { m_MoveInfo.m_UseGravity = useGravity; }

	void AddMove(VECTOR move);
	void AddRot(float rotY);

	void SetCollision(std::weak_ptr<CollisionBase> collision);
	void SetCollPosOffset(VECTOR posOffset) { m_CollInfo.m_PosOffset = posOffset; }
	void SetCollScaleOffset(VECTOR scaleOffset) { m_CollInfo.m_ScaleOffset = scaleOffset; }
	void AddPushBack(VECTOR pushBack) 
	{ 
		m_CollInfo.m_CollisionPushBack = VAdd(m_CollInfo.m_CollisionPushBack, pushBack);
	}

	void CollisionPushBack()
	{
		if (!MyMath::IsVecZero(m_CollInfo.m_CollisionPushBack))
		{
			m_Transform.m_Pos = VAdd(m_Transform.m_Pos, m_CollInfo.m_CollisionPushBack);
		}
	}

	template <typename T>
	std::shared_ptr<T> GetCollision()
	{
		auto collPtr = m_CollInfo.m_Collision.lock();
		if (!collPtr) return nullptr;

		return std::dynamic_pointer_cast<T>(collPtr);
	}

	VECTOR GetPos() const { return m_Transform.m_Pos; }
	VECTOR GetRot() const { return m_Transform.m_Rot; }
	VECTOR GetScale() const { return m_Transform.m_Scale; }
	VECTOR GetMove() const { return m_MoveInfo.m_Move; }

	VECTOR GetForward() const
	{
		VECTOR result = MyMath::VecZero();
		result.x = sinf(m_MoveInfo.m_DirAngleY);
		result.z = cosf(m_MoveInfo.m_DirAngleY);

		return result;
	}

	void SetDirAngleY(float angle)
	{
		m_MoveInfo.m_DirAngleY = angle; 

		if (m_MoveInfo.m_DirAngleY >= DX_TWO_PI_F)
		{
			m_MoveInfo.m_DirAngleY -= DX_TWO_PI_F;
		}
	}

	float GetDirAngleY() const { return m_MoveInfo.m_DirAngleY; }

private:
	struct Transform
	{
		VECTOR m_Pos;
		VECTOR m_Rot;
		VECTOR m_Scale;
		VECTOR m_PrevPos;
	};

	struct MoveInfo
	{
		VECTOR m_Move;
		float m_DirAngleY;
		float m_Gravity;
		bool m_UseGravity;
	};

	struct CollInfo
	{
		std::weak_ptr<CollisionBase> m_Collision;
		VECTOR m_PosOffset;
		VECTOR m_ScaleOffset;
		VECTOR m_CollisionPushBack;
	};
	
	Transform m_Transform;
	MoveInfo m_MoveInfo;
	CollInfo m_CollInfo;
};