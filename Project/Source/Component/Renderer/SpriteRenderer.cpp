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
	m_RectTransform.m_ExRate = 0.0f;
	m_RectTransform.m_Angle = 0.0f;

	m_Alpha = 0.0f;
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
}

void SpriteRenderer::Draw()
{
	if (!m_Active) return;

	int posX = static_cast<int>(m_RectTransform.m_Pos.x);
	int posY = static_cast<int>(m_RectTransform.m_Pos.y);
	double exRate = static_cast<double>(m_RectTransform.m_ExRate);
	double angle = static_cast<double>(m_RectTransform.m_Angle);

	int bright = static_cast<int>(255.0f * m_Alpha);

	SetDrawBright(bright, bright, bright);

	DrawRotaGraph(posX, posY, exRate, angle, m_SpriteHandle, TRUE);

	SetDrawBright(255, 255, 255);
}