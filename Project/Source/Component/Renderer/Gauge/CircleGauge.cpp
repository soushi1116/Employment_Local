#include "CircleGauge.h"
#include "../../GameObject.h"
#include "../../../MyColor/MyColor.h"

CircleGauge::CircleGauge(GameObject* owner, const char* filePath) : GaugeBase(owner, filePath)
{
	m_MaxAngle = 0.0f;
	m_CurrentAngle = 0.0f;
}

CircleGauge::~CircleGauge()
{

}

void CircleGauge::Start()
{
	GaugeBase::Start();

	
}

void CircleGauge::Update()
{
	GaugeBase::Update();

	auto parameterPtr = m_ParentParameter.lock();

	if (!parameterPtr) return;

	m_CurrentAngle = m_MaxAngle * m_Percentage;
}

void CircleGauge::Draw()
{
	//if (!m_Active) return;

	DrawCircleGauge(m_RectTransform.m_Pos.x, m_RectTransform.m_Pos.y, m_Percentage, m_Handle);
}