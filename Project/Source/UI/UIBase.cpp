#include "UIBase.h"
#include "../MyMath/MyMath.h"

UIBase::UIBase()
{
	m_Pos = MyMath::VecZero();
	m_Handle = 0;
	m_Type = UI_TYPE_NONE;
}

UIBase::~UIBase()
{
	Fin();
}

void UIBase::Init()
{

}

void UIBase::Load()
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
	case UI_RESULT_WIN:
		m_Handle = LoadGraph("Data/UI/ResultScene/Result_Win.png");
		break;
	case UI_RESULT_LOSE:
		m_Handle = LoadGraph("Data/UI/ResultScene/Result_Lose.png");
		break;
	case UI_ONE_MORE_BATTLE:
		m_Handle = LoadGraph("Data/UI/ResultScene/OneMoreBattle.png");
		break;
	case UI_TO_HOME:
		m_Handle = LoadGraph("Data/UI/ResultScene/ToHome.png");
		break;
	case UI_TYPE_MAX:
		break;
	case UI_TYPE_NONE:
		break;
	default:
		break;
	}
}

void UIBase::Start()
{

}

void UIBase::Step()
{

}

void UIBase::Update()
{

}

void UIBase::Draw()
{
	DrawRotaGraph(m_Pos.x, m_Pos.y, 1.0, 0.0, m_Handle, TRUE);
}

void UIBase::Fin()
{
	DeleteGraph(m_Handle);
}