#include "GaugeBase.h"
#include "../../GameObject.h"
#include "../../../MyColor/MyColor.h"

GaugeBase::GaugeBase(GameObject* owner, const char* filePath) : RendererBase(owner, filePath)
{
	m_Handle = LoadGraph(filePath);
	m_Percentage = 0.0f;

	m_RectTransform.m_Pos = MyMath::VecZero();
	m_RectTransform.m_Center = MyMath::VecZero();
	m_RectTransform.m_ExRate = MyMath::VecZero();
	m_RectTransform.m_Angle = 0.0f;
	m_RectTransform.m_GraphSize = MyMath::Vec2DInt(0, 0);

	m_Type = GAUGE_TYPE_NONE;
	m_Pos = MyMath::VecZero();
	m_ExRate = MyMath::VecZero();
	m_Angle = 0.0f;
}

GaugeBase::~GaugeBase()
{

}

void GaugeBase::Start()
{
	m_RayerIndex = 2;
}

void GaugeBase::Update()
{
	auto parameterPtr = m_ParentParameter.lock();

	if (!parameterPtr) return;

	float currentNum = 0.0f, maxNum = 0.0f;

	switch (m_Type)
	{
	case CHARACTER_HP_GAUGE:
	{
		currentNum = static_cast<float>(parameterPtr->GetHp());
		maxNum = static_cast<float>(parameterPtr->GetMaxHp());

		break;
	}
	case CHARACTER_SKILL_GAUGE:
	{
		currentNum = static_cast<float>(parameterPtr->GetSkillPoint());
		maxNum = static_cast<float>(SKILL_AND_SUPER_ATTACK_POINT_MAX);

		break;
	}
	case CHARACTER_SUPER_ATTACK_GAUGE:
	{
		currentNum = static_cast<float>(parameterPtr->GetSuperAttackPoint());
		maxNum = static_cast<float>(SKILL_AND_SUPER_ATTACK_POINT_MAX);

		break;
	}
	case GAUGE_TYPE_MAX:
		break;
	case GAUGE_TYPE_NONE:
		break;
	default:
		break;
	}

	m_Percentage = currentNum / maxNum;
}