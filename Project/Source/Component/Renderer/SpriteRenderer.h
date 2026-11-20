#pragma once
#include "RendererBase.h"
#include "DxLib.h"
#include <memory>
#include "../../MyMath/MyMath.h"

class GameObject;

class SpriteRenderer : public RendererBase
{
public:
	SpriteRenderer(GameObject* owner, const char* filePath);

	~SpriteRenderer();

	void Start() override;
	void Update()override;
	void Draw() override;

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetExRate(VECTOR exRate) { m_RectTransform.m_ExRate = exRate; }
	void SetAngle(float angle) { m_RectTransform.m_Angle = angle; }
	void SetBright(float bright) { m_Bright = bright; }
	void SetActive(bool active) { m_Active = active; }

	void SetAlpha(int alpha) { m_Alpha = alpha; }

	VECTOR GetPos() const { return m_RectTransform.m_Pos; }
	VECTOR GetExRate() const { return m_RectTransform.m_ExRate; }
	MyMath::VECTOR_INT GetGraphScale() const { return m_RectTransform.m_GraphSize; }

	int GetBlinkState() { return m_BlinkState; }

private:
	bool m_Active;

	float m_Bright;

	int m_SpriteHandle = -1;
	RectTransform m_RectTransform;
};