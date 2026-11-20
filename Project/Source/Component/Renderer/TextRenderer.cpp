#include "TextRenderer.h"
#include "../../MyMath/MyMath.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../Managers/RendererManager/RendererManager.h"
#include "../../MyColor/MyColor.h"

TextRenderer::TextRenderer(GameObject* owner, const char* filePath)
	: RendererBase(owner, filePath)
	, m_Pos(MyMath::VecZero())
	, m_Alpha(0.0f)
	, m_Active(false)
	, m_FontHandle(0)
	, m_FontType(FONT_HANDLE_NONE)
	, m_Color(COLOR_BLACK)

{
	for (int i = 0; i < UI_TEXT_MAX; i++)
	{
		m_Text[i] = 0;
	}
}



TextRenderer::~TextRenderer()
{
	
}

void TextRenderer::Start()
{
	m_Active = true;

	m_Alpha = 255;

	m_RayerIndex = 3;

	m_FontHandle = RendererManager::GetInstance()->GetFontHandle(m_FontType);
}

void TextRenderer::Update()
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



void TextRenderer::Draw()
{
	if (m_Active)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_Alpha);

		DrawStringToHandle((int)m_Pos.x, (int)m_Pos.y, m_Text, m_Color, m_FontHandle);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	}
}