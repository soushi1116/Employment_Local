#include "LineGauge.h"
#include "../../GameObject.h"
#include "../../../MyColor/MyColor.h"

LineGauge::LineGauge(GameObject* owner, const char* filePath) : GaugeBase(owner, filePath)
{
	m_MaxExrateX = 0.0f;
	m_MaxPosX = 0.0f;
	m_GraphSizeX = 0;
	m_LeftFixed = 0.0f;
}

LineGauge::~LineGauge()
{

}

void LineGauge::Start()
{
	GaugeBase::Start();

	m_LeftFixed = m_MaxPosX - static_cast<float>(m_GraphSizeX) * m_MaxExrateX * 0.5f;
}

void LineGauge::Update()
{
	GaugeBase::Update();

	auto parameterPtr = m_ParentParameter.lock();

	if (!parameterPtr) return;

	m_RectTransform.m_ExRate.x = m_MaxExrateX * m_Percentage;
}

void LineGauge::Draw()
{
	//if (!m_Active) return;

	int posX = static_cast<int>(m_RectTransform.m_Pos.x);
	int posY = static_cast<int>(m_RectTransform.m_Pos.y);
	int centerX = static_cast<int>(m_RectTransform.m_Center.x);
	int centerY = static_cast<int>(m_RectTransform.m_Center.y);
	double exRateX = static_cast<double>(m_RectTransform.m_ExRate.x);
	double exRateY = static_cast<double>(m_RectTransform.m_ExRate.y);
	double angle = static_cast<double>(m_RectTransform.m_Angle);

	DrawRotaGraph3(posX, posY, centerX, centerY, exRateX, exRateY, angle, m_Handle, TRUE);
}