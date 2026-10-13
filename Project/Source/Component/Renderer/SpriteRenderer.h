#pragma once
#include "../Component.h"
#include "DxLib.h"
#include <memory>

class GameObject;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* owner, const char* filePath);

	~SpriteRenderer();

	void Start();
	void Draw();

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetExRate(float exRate) { m_RectTransform.m_ExRate = exRate; }
	void SetAngle(float angle) { m_RectTransform.m_Angle = angle; }
	void SetAlpha(float alpha) { m_Alpha = alpha; }

private:
	struct RectTransform
	{
		VECTOR m_Pos;
		float m_ExRate;
		float m_Angle;
	};

	float m_Alpha;

	int m_SpriteHandle = -1;
	RectTransform m_RectTransform;
};