#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class CharacterParameter;
class SpriteRenderer;

class Gauge : public Component
{
public:
	Gauge(GameObject* owner);
	~Gauge();

	void Start() override;
	void Update() override;

	void SetParentParameter(CharacterParameter* parameter) { m_ParentParameter = parameter; }
	void SetParentRenderer(SpriteRenderer* renderer) { m_ParentRenderer = renderer; }

private:
	CharacterParameter* m_ParentParameter;
	SpriteRenderer* m_ParentRenderer;

	float m_Percentage;
	float m_MaxExrateX;
	float m_MaxPosX;
	float m_LeftFixed;
	int m_GraphSizeX;
};

