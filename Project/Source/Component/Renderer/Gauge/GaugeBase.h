#pragma once
#include "../RendererBase.h"
#include <memory>
#include "DxLib.h"

class GameObject;
class CharacterParameter;
class SpriteRenderer;

class GaugeBase : public RendererBase
{
public:
	GaugeBase(GameObject* owner, const char* filePath);
	~GaugeBase();

	void Start() override;
	void Update() override;

	void SetParentParameter(std::shared_ptr<CharacterParameter> parameter) { m_ParentParameter = parameter; }
	void SetGaugeType(GaugeType type) { m_Type = type; }

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetExRate(VECTOR exRate) { m_RectTransform.m_ExRate = exRate; }
	void SetAngle(float angle) { m_RectTransform.m_Angle = angle; }

protected:
	std::weak_ptr<CharacterParameter> m_ParentParameter;

	RectTransform m_RectTransform;

	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_ExRate;
	float m_Angle;
	float m_Percentage;
	GaugeType m_Type;
};

