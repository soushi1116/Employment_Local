#pragma once
#include "DxLib.h"
#include "../../Component.h"

class GameObject;

class CollisionBase
{
public:
	CollisionBase();
	~CollisionBase();

	virtual void Draw() = 0;

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetPosOffset(VECTOR offset) { m_PosOffset = offset; }
	void SetSize(VECTOR size) { m_Size = size; }

	VECTOR GetPos() const { return m_Pos; }
	VECTOR GetSize() const { return m_Size; }

protected:
	VECTOR m_Pos;
	VECTOR m_PosOffset;
	VECTOR m_Size;
};