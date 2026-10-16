#include "Gauge.h"
#include "../GameObject.h"

Gauge::Gauge(GameObject* owner) : Component(owner)
{
	m_Percentage = 0.0f;
	m_MaxExrateX = 0.0f;
	m_MaxPosX = 0.0f;
	m_GraphSizeX = 0;
}

Gauge::~Gauge()
{

}

void Gauge::Start()
{
	m_MaxExrateX = m_ParentRenderer->GetExRate().x;
	m_MaxPosX = m_ParentRenderer->GetPos().x;
	m_GraphSizeX = m_ParentRenderer->GetGraphScale().x;
}

void Gauge::Update()
{
	float currentHp = static_cast<float>(m_ParentParameter->GetHp());
	float maxHp = static_cast<float>(m_ParentParameter->GetMaxHp());

	m_Percentage = currentHp / maxHp;

	float newExRate = m_MaxExrateX * m_Percentage;
	float newPos = m_MaxPosX - static_cast<float>(m_GraphSizeX) * m_Percentage / 2;

	m_ParentRenderer->SetPos(VGet(newPos, m_ParentRenderer->GetPos().y, m_ParentRenderer->GetPos().z));
	m_ParentRenderer->SetExRate(VGet(newExRate, m_ParentRenderer->GetExRate().y, m_ParentRenderer->GetExRate().z));
}