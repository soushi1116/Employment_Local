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
	case UI_BUTTON_BATTLE:
		m_Handle = LoadGraph("Data/UI/HomeScene/Battle.png");
		break;
	case UI_BUTTON_OPTION:
		m_Handle = LoadGraph("Data/UI/HomeScene/Option.png");
		break;
	case UI_BUTTON_SOUND:
		m_Handle = LoadGraph("Data/UI/OptionScene/Sound.png");
		break;
	case UI_BUTTON_MANUAL:
		m_Handle = LoadGraph("Data/UI/OptionScene/Manual.png");
		break;
	case UI_BUTTON_BOSS:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/Boss.png");
		break;
	case UI_BUTTON_PLAYER:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/Player.png");
		break;
	case UI_BUTTON_KNIGHT:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Knight.png");
		break;
	case UI_BUTTON_BOT:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Bot.png");
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