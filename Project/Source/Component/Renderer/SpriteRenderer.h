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

	void Start() override;
	void Update()override;
	void Draw() override;

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetExRate(VECTOR exRate) { m_RectTransform.m_ExRate = exRate; }
	void SetAngle(float angle) { m_RectTransform.m_Angle = angle; }
	void SetBright(float bright) { m_Bright = bright; }
	void SetActive(bool active) { m_Active = active; }

	void SetAlpha(int alpha) { m_Alpha = alpha; }
	void BlinkStart(int speed, bool isRoop) { m_BlinkSpeed = speed; m_IsRoopBlink = isRoop; m_BlinkState = 1; }

	VECTOR GetPos() const { return m_RectTransform.m_Pos; }
	VECTOR GetExRate() const { return m_RectTransform.m_ExRate; }
	MyMath::VECTOR_INT GetGraphScale() const { return m_RectTransform.m_GraphSize; }

	int GetBlinkState() { return m_BlinkState; }

private:
	struct RectTransform
	{
		VECTOR m_Pos;
		VECTOR m_Center;
		VECTOR m_ExRate;
		float m_Angle;
		MyMath::VECTOR_INT m_GraphSize;
	};

	float m_Bright;
	bool m_Active;

	int m_Alpha;
	// 点滅状態（-1:減少、0：点滅しない、1:増加）
	int m_BlinkState;
	// 点滅速度
	int m_BlinkSpeed;

	bool m_IsRoopBlink;

	int m_SpriteHandle = -1;
	RectTransform m_RectTransform;
};