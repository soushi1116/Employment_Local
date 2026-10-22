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

	void SetParentParameter(std::shared_ptr<CharacterParameter> parameter) { m_ParentParameter = parameter; }
	void SetParentRenderer(std::shared_ptr<SpriteRenderer> renderer) { m_ParentRenderer = renderer; }

private:
	std::weak_ptr<CharacterParameter> m_ParentParameter;
	std::weak_ptr<SpriteRenderer> m_ParentRenderer;

	float m_Percentage;
	float m_MaxExrateX;
	float m_MaxPosX;
	float m_LeftFixed;
	int m_GraphSizeX;
};

