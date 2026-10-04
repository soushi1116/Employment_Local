#pragma once

#include "DxLib.h"
#include "../Component.h"
#include <memory>

class CollisionBase;

class _3DPhysics : public Component
{
public:
	_3DPhysics(GameObject* owner);
	~_3DPhysics();

	void Step();
	void Update();

	GameObject* GetOwner() { return m_Owner; }

	void SetCollision(CollisionBase* collision);

	void SetPos(VECTOR pos) { m_Transform.m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Transform.m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Transform.m_Scale = scale; }

	template <typename T>
	T* GetCollison()
	{
		return dynamic_cast<T*>(m_Collision);
	}

	VECTOR GetPos() { return m_Transform.m_Pos; }
	VECTOR Getrot() { return m_Transform.m_Rot; }
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
	};
	
	Transform m_Transform;
	MoveInfo m_MoveInfo;

	CollisionBase* m_Collision;
};