#pragma once

#include "DxLib.h"
#include "../Component.h"
#include <memory>
#include "../../MyMath/MyMath.h"

class CollisionBase;

class _3DPhysics : public Component
{
public:
	_3DPhysics(GameObject* owner);
	~_3DPhysics();

	void Step() override;
	void Update() override;
	void Draw() override;

	GameObject* GetOwner() { return m_Owner; }

	void SetPos(VECTOR pos) { m_Transform.m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Transform.m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Transform.m_Scale = scale; }
	void SetUseGravity(bool useGravity) { m_MoveInfo.m_UseGravity = useGravity; }

	void AddMove(VECTOR move);

	void SetCollision(CollisionBase* collision);
	void SetCollPosOffset(VECTOR posOffset) { m_CollInfo.m_PosOffset = posOffset; }
	void SetCollScaleOffset(VECTOR scaleOffset) { m_CollInfo.m_ScaleOffset = scaleOffset; }

	void HitFloor();

	template <typename T>
	T* GetCollison()
	{
		return dynamic_cast<T*>(m_CollInfo.m_Collision);
	}

	VECTOR GetPos() { return m_Transform.m_Pos; }
	VECTOR GetRot() { return m_Transform.m_Rot; }
	VECTOR GetScale() { return m_Transform.m_Scale; }

private:
	struct Transform
	{
		VECTOR m_Pos;
		VECTOR m_Rot;
		VECTOR m_Scale;
	};

	struct MoveInfo
	{
		VECTOR m_Move;
		float m_Gravity;
		bool m_UseGravity;
	};

	struct CollInfo
	{
		CollisionBase* m_Collision;
		VECTOR m_PosOffset;
		VECTOR m_ScaleOffset;
	};
	
	Transform m_Transform;
	MoveInfo m_MoveInfo;
	CollInfo m_CollInfo;
};