#pragma once
#include "../Component.h"
#include "DxLib.h"
#include <memory>
#include "../../MyMath/MyMath.h"

class GameObject;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* owner, const char* filePath);

	~SpriteRenderer();

	void Start();
	void Draw();

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetExRate(VECTOR exRate) { m_RectTransform.m_ExRate = exRate; }
	void SetAngle(float angle) { m_RectTransform.m_Angle = angle; }
	void SetAlpha(float alpha) { m_Alpha = alpha; }
	void SetActive(bool active) { m_Active = active; }

	VECTOR GetPos() const { return m_RectTransform.m_Pos; }
	VECTOR GetExRate() const { return m_RectTransform.m_ExRate; }
	MyMath::VECTOR_INT GetGraphScale() const { return m_RectTransform.m_GraphSize; }

private:
	struct RectTransform
	{
		VECTOR m_Pos;
		VECTOR m_Center;
		VECTOR m_ExRate;
		float m_Angle;
		MyMath::VECTOR_INT m_GraphSize;
	};

	float m_Alpha;
	bool m_Active;

	int m_SpriteHandle = -1;
	RectTransform m_RectTransform;
};