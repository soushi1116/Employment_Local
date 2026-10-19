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
	m_MaxExrateX = m_ParentRenderer->GetExRate().x;
	m_MaxPosX = m_ParentRenderer->GetPos().x;
	m_GraphSizeX = m_ParentRenderer->GetGraphScale().x;
	m_LeftFixed = m_MaxPosX - static_cast<float>(m_GraphSizeX) * m_MaxExrateX * 0.5f;
}

void Gauge::Update()
{
	float currentHp = static_cast<float>(m_ParentParameter->GetHp());
	float maxHp = static_cast<float>(m_ParentParameter->GetMaxHp());

	m_Percentage = currentHp / maxHp;

	float newExRate = m_MaxExrateX * m_Percentage;
	float offsetX = static_cast<float>(m_GraphSizeX) * newExRate * 0.5f;
	float newPos = m_LeftFixed + offsetX;

	m_ParentRenderer->SetPos(VGet(newPos, m_ParentRenderer->GetPos().y, m_ParentRenderer->GetPos().z));
	m_ParentRenderer->SetExRate(VGet(newExRate, m_ParentRenderer->GetExRate().y, m_ParentRenderer->GetExRate().z));
}