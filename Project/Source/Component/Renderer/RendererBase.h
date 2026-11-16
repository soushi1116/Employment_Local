#pragma once
#include "DxLib.h"
#include "../Component.h"
#include "../../MyMath/MyMath.h"

class GameObject;

class RendererBase : public Component
{
public:
	RendererBase(GameObject* owner, const char* filePath) : Component(owner) {}
	~RendererBase() {}

public:
	void SetRayerIndex(int index) { m_RayerIndex = index; }
	int GetRayerIndex() const { return m_RayerIndex; }

protected:
	int m_RayerIndex = 0;

	struct RectTransform
	{
		VECTOR m_Pos = MyMath::VecZero();
		VECTOR m_Center = MyMath::VecZero();
		VECTOR m_ExRate = MyMath::VecZero();
		float m_Angle = 0.0f;
		MyMath::VECTOR_INT m_GraphSize = MyMath::Vec2DInt(0, 0);
	};
};

