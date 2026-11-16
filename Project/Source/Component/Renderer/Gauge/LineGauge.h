#pragma once
#include "GaugeBase.h"
#include <memory>
#include "DxLib.h"

class LineGauge : public GaugeBase
{
public:
	LineGauge(GameObject* owner, const char* filePath);
	~LineGauge();

	void Start() override;
	void Update() override;
	void Draw() override;

public:
	void SetMaxExRateX(float exRate) { m_MaxExrateX = exRate; }

private:
	float m_MaxExrateX;
	float m_MaxPosX;
	float m_LeftFixed;
	int m_GraphSizeX;
};

