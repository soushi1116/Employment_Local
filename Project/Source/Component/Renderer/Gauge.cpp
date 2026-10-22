#include "Gauge.h"
#include "../GameObject.h"
#include "../../MyColor/MyColor.h"

Gauge::Gauge(GameObject* owner) : Component(owner)
{
	m_Percentage = 0.0f;
	m_MaxExrateX = 0.0f;
	m_MaxPosX = 0.0f;
	m_GraphSizeX = 0;
	m_LeftFixed = 0.0f;
}

Gauge::~Gauge()
{

}

void Gauge::Start()
{
	if (auto rendererPtr = m_ParentRenderer.lock())
	{
		m_MaxExrateX = rendererPtr->GetExRate().x;
		m_MaxPosX = rendererPtr->GetPos().x;
		m_GraphSizeX = rendererPtr->GetGraphScale().x;
		m_LeftFixed = m_MaxPosX - static_cast<float>(m_GraphSizeX) * m_MaxExrateX * 0.5f;
	}
}

void Gauge::Update()
{
	auto parameterPtr = m_ParentParameter.lock();
	auto rendererPtr = m_ParentRenderer.lock();

	if (!parameterPtr || !rendererPtr) return;

	float currentHp = static_cast<float>(parameterPtr->GetHp());
	float maxHp = static_cast<float>(parameterPtr->GetMaxHp());

	m_Percentage = currentHp / maxHp;

	float newExRate = m_MaxExrateX * m_Percentage;
	float offsetX = static_cast<float>(m_GraphSizeX) * newExRate * 0.5f;
	float newPos = m_LeftFixed + offsetX;

	rendererPtr->SetPos(VGet(newPos, rendererPtr->GetPos().y, rendererPtr->GetPos().z));
	rendererPtr->SetExRate(VGet(newExRate, rendererPtr->GetExRate().y, rendererPtr->GetExRate().z));
}