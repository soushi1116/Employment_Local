#pragma once
#include "DxLib.h"
#include "../../Component.h"

class GameObject;

class CollisionBase : public Component
{
public:
	CollisionBase(GameObject* owner);
	~CollisionBase();

	virtual void Draw() = 0;

	void SetPosOffset(VECTOR offset) { m_PosOffset = offset; }

protected:
	VECTOR m_Pos;
	VECTOR m_PosOffset;
	GameObject* m_Owner;
};