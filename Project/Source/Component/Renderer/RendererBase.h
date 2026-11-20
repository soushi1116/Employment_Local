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

	void BlinkStart(int speed, bool isRoop) { m_BlinkSpeed = speed; m_IsRoopBlink = isRoop; m_BlinkState = 1; }

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

	int m_Alpha = 0;
	// 点滅状態（-1:減少、0：点滅しない、1:増加）
	int m_BlinkState = 0;
	// 点滅速度
	int m_BlinkSpeed = 0;

	bool m_IsRoopBlink = false;
};

