#include "../Component.h"
#include "SpriteRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

SpriteRenderer::SpriteRenderer(GameObject* owner, const char* filePath)
	: RendererBase(owner, filePath)
	, m_SpriteHandle(LoadGraph(filePath))
	, m_RectTransform{ MyMath::VecZero(), MyMath::VecZero(), MyMath::VecZero(), 0.0f, MyMath::Vec2DInt(0, 0) }
	, m_Active(false)
	, m_Bright(0.0f)
{

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
	m_Bright = 1.0f;
	m_Alpha = 255;

	m_Active = true;

	m_RayerIndex = 2;

	GetGraphSize(m_SpriteHandle, &m_RectTransform.m_GraphSize.x, &m_RectTransform.m_GraphSize.y);

	m_RectTransform.m_Center.x = static_cast<float>(m_RectTransform.m_GraphSize.x) / 2.0f;
	m_RectTransform.m_Center.y = static_cast<float>(m_RectTransform.m_GraphSize.y) / 2.0f;

	if (m_Owner->CompareTag(TAG_MISSION))
	{
		
		m_Alpha = m_Alpha * 4 / 5;
	}
}

void SpriteRenderer::Update()
{
	if (!m_Active) return;

	if (m_BlinkState != 0)
	{
		m_Alpha += m_BlinkState * m_BlinkSpeed;

		if (m_Alpha >= 255)
		{
			m_Alpha = 255;

			// 減少へ
			m_BlinkState = -1;
		}
		else if (m_Alpha <= 0)
		{
			m_Alpha = 0;

			// ループするなら増加へ、しないなら点滅終了
			if (m_IsRoopBlink)
			{
				m_BlinkState = 1;
			}
			else
			{
				m_BlinkState = 0;
			}
		}
	}
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

	int bright = static_cast<int>(255.0f * m_Bright);

	SetDrawBright(bright, bright, bright);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);

	DrawRotaGraph3(posX, posY, centerX, centerY, exRateX, exRateY ,angle, m_SpriteHandle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	SetDrawBright(255, 255, 255);
}