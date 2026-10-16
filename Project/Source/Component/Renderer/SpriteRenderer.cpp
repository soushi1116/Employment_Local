#include "../Component.h"
#include "SpriteRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

SpriteRenderer::SpriteRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_SpriteHandle = LoadGraph(filePath);
	
	m_CompName = "Sprite";

	m_RectTransform.m_Pos = MyMath::VecZero();
	m_RectTransform.m_Center = MyMath::VecZero();
	m_RectTransform.m_ExRate = MyMath::VecZero();
	m_RectTransform.m_Angle = 0.0f;
	m_RectTransform.m_GraphSize = MyMath::Vec2DInt(0, 0);

	m_Alpha = 0.0f;

	m_Active = false;
}

SpriteRenderer::~SpriteRenderer()
{
	if (m_SpriteHandle != -1)
	{
		DeleteGraph(m_SpriteHandle);
	}
}

void SpriteRenderer::Start()
{
	m_Alpha = 1.0f;

	m_Active = true;

	GetGraphSize(m_SpriteHandle, &m_RectTransform.m_GraphSize.x, &m_RectTransform.m_GraphSize.y);

	m_RectTransform.m_Center.x = static_cast<float>(m_RectTransform.m_GraphSize.x) / 2.0f;
	m_RectTransform.m_Center.y = static_cast<float>(m_RectTransform.m_GraphSize.y) / 2.0f;
}

void SpriteRenderer::Draw()
{
	if (!m_Active) return;

	int posX = static_cast<int>(m_RectTransform.m_Pos.x);
	int posY = static_cast<int>(m_RectTransform.m_Pos.y);
	int centerX = static_cast<int>(m_RectTransform.m_Center.x);
	int centerY = static_cast<int>(m_RectTransform.m_Center.y);
	double exRateX = static_cast<double>(m_RectTransform.m_ExRate.x);
	double exRateY = static_cast<double>(m_RectTransform.m_ExRate.y);
	double angle = static_cast<double>(m_RectTransform.m_Angle);

	int bright = static_cast<int>(255.0f * m_Alpha);

	SetDrawBright(bright, bright, bright);

	DrawRotaGraph3(posX, posY, centerX, centerY, exRateX, exRateY ,angle, m_SpriteHandle, TRUE);

	SetDrawBright(255, 255, 255);
}