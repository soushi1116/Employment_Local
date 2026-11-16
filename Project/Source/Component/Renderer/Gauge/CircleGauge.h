#pragma once
#include "GaugeBase.h"
#include <memory>
#include "DxLib.h"

class CircleGauge : public GaugeBase
{
public:
	CircleGauge(GameObject* owner, const char* filePath);
	~CircleGauge();

	void Start() override;
	void Update() override;
	void Draw() override;

public:
	void SetMaxAngle(float angle) { m_MaxAngle = angle; }

private:
	float m_MaxAngle;
	float m_CurrentAngle;
};

