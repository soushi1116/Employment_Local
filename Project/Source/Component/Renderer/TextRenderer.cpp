#include "TextRenderer.h"
#include "../../MyMath/MyMath.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../Managers/RendererManager/RendererManager.h"

TextRenderer::TextRenderer(GameObject* owner, const char* filePath) : RendererBase(owner, filePath)
{
	m_CompName = "Text";

	m_Pos = MyMath::VecZero();

	m_Alpha = 0.0f;

	m_Active = false;

	for (int i = 0; i < UI_TEXT_MAX; i++)
	{
		m_Text[i] = 0;
	}

	m_FontHandle = 0;
	m_FontType = FONT_HANDLE_NONE;
	m_Color = GetColor(0, 0, 0);
}

TextRenderer::~TextRenderer()
{
	
}

void TextRenderer::Start()
{
	m_Active = true;

	m_RayerIndex = 3;

	m_FontHandle = RendererManager::GetInstance()->GetFontHandle(m_FontType);
}

void TextRenderer::Step()
{

}

void TextRenderer::Draw()
{
	if (m_Active)
	{
		DrawStringToHandle((int)m_Pos.x, (int)m_Pos.y, m_Text, m_Color, m_FontHandle);
	}
}