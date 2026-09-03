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
	case UI_BUTTON_BGM:
		m_Handle = LoadGraph("Data/UI/OptionScene/BGM.png");
		break;
	case UI_BUTTON_SE:
		m_Handle = LoadGraph("Data/UI/OptionScene/SE.png");
		break;
	case UI_BUTTON_PLAYER:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/Player.png");
		break;
	case UI_BUTTON_CPU1:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/CPU1.png");
		break;
	case UI_BUTTON_CPU2:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/CPU2.png");
		break;
	case UI_BUTTON_CPU3:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/CPU3.png");
		break;
	case UI_BUTTON_KNIGHT:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Knight.png");
		break;
	case UI_BUTTON_NINJA:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Ninja.png");
		break;
	case UI_BUTTON_FAIRY:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Fairy.png");
		break;
	case UI_BUTTON_ROBOT:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Robot.png");
		break;
	case UI_BUTTON_BEAST:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/Beast.png");
		break;
	case UI_BUTTON_TEST_MAP:
		m_Handle = LoadGraph("Data/UI/MapSelectScene/TestMap.png");
		break;
	case UI_BUTTON_FACTORY:
		m_Handle = LoadGraph("Data/UI/MapSelectScene/Factory.png");
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
	m_Active = true;
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