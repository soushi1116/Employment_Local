#pragma once
#include "DxLib.h"
#include "../MyMath/MyMath.h"
#include "Component.h"

class GameObject;

class Transform : public Component
{
public:
	Transform(GameObject* owner);

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRotation(VECTOR rot) { m_Rot = rot; }
	void SetScale(VECTOR scale) { m_Scale = scale; }

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetScale() { return m_Scale; }

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};