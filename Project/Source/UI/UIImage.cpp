#include "UIImage.h"
#include "../MyMath/MyMath.h"

UIImage::UIImage() : UIBase()
{
	
}

UIImage::~UIImage()
{
	Fin();
}

void UIImage::Init()
{

}

void UIImage::Load()
{
	switch (m_Name)
	{
	case UI_HOME:
		m_Handle = LoadGraph("Data/UI/HomeScene/Home.png");
		break;
	case UI_CHARACTER_SELECT:
		m_Handle = LoadGraph("Data/UI/CharacterSelectScene/CharacterSelect.png");
		break;
	case UI_BOSS_SELECT:
		m_Handle = LoadGraph("Data/UI/BossSelectScene/BossSelect.png");
		break;
	case UI_BUTTON_A:
		m_Handle = LoadGraph("Data/UI/Mission/A-Button.png");
		break;
	case UI_BUTTON_B:
		m_Handle = LoadGraph("Data/UI/Mission/B-Button.png");
		break;
	case UI_BUTTON_X:
		m_Handle = LoadGraph("Data/UI/Mission/X-Button.png");
		break;
	case UI_BUTTON_Y:
		m_Handle = LoadGraph("Data/UI/Mission/Y-Button.png");
		break;
	case UI_SKILL:
		m_Handle = LoadGraph("Data/UI/BattleScene/Skill.png");
		break;
	case UI_SUPER_ATTACK:
		m_Handle = LoadGraph("Data/UI/BattleScene/SuperAttack.png");
		break;
	case UI_RESULT_WIN:
		m_Handle = LoadGraph("Data/UI/ResultScene/Result_Win.png");
		break;
	case UI_RESULT_LOSE:
		m_Handle = LoadGraph("Data/UI/ResultScene/Result_Lose.png");
		break;
	case UI_NAME_MAX:
		break;
	case UI_NAME_NONE:
		break;
	default:
		break;
	}
}

void UIImage::Start()
{

}

void UIImage::Step()
{

}