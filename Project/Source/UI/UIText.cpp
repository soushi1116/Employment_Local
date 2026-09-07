#include "UIText.h"
#include "../MyMath/MyMath.h"

UIText::UIText() : UIBase()
{
	for (int i = 0; i < UI_TEXT_MAX; i++)
	{
		m_Text[i] = 0;
	}

	m_FontHandle = 0;
	m_Color = GetColor(0, 0, 0);
}

UIText::~UIText()
{
	Fin();
}

void UIText::Init()
{

}

void UIText::Load(int scale)
{
	m_FontHandle = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", scale, -1);
}

void UIText::Start()
{
	m_Active = true;
}

void UIText::Step()
{

}

void UIText::Draw()
{
	UIBase::Draw();

	if (m_Active)
	{
		DrawStringToHandle((int)m_Pos.x, (int)m_Pos.y, m_Text, m_Color, m_FontHandle);
	}
}