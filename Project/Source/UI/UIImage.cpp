#include "UIImage.h"

UIImage::UIImage()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Handle = 0;
	m_Type = UI_TYPE_NONE;
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
	switch (m_Type)
	{
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
	case UI_TYPE_MAX:
		break;
	case UI_TYPE_NONE:
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

void UIImage::Update()
{

}

void UIImage::Draw()
{
	DrawGraph(m_Pos.x, m_Pos.y, m_Handle, TRUE);
}

void UIImage::Fin()
{
	DeleteGraph(m_Handle);
}