#include "UIButton.h"
#include "UIManager.h"

UIButton::UIButton() : UIBase()
{
	m_IsSelected = false;
	m_Index = MyMath::Vec2DInt(0, 0);
}

UIButton::~UIButton()
{
	Fin();
}

void UIButton::Init()
{

}

void UIButton::Load()
{
	switch (m_Name)
	{
	case UI_BUTTON_PARENT:
		m_Handle = LoadGraph("Data/UI/ParentSelectScene/Parent.png");
		break;
	case UI_BUTTON_CHILD:
		m_Handle = LoadGraph("Data/UI/ParentSelectScene/Child.png");
		break;
	case UI_BUTTON_ONE_MORE_BATTLE:
		m_Handle = LoadGraph("Data/UI/ResultScene/OneMoreBattle.png");
		break;
	case UI_BUTTON_TO_HOME:
		m_Handle = LoadGraph("Data/UI/ResultScene/ToHome.png");
		break;

	case UI_NAME_MAX:
		break;
	case UI_NAME_NONE:
		break;
	default:
		break;
	}
}

void UIButton::Start()
{

}

void UIButton::Step()
{
	m_IsSelected = false;
}

void UIButton::Draw()
{
	if (!m_IsSelected)
	{
		SetDrawBright(128, 128, 128);
	}

	UIBase::Draw();

	SetDrawBright(255, 255, 255);
}