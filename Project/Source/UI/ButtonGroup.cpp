#include "ButtonGroup.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"

const int CURSOR_MOVE_INTERVAL = 20;

ButtonGroup::ButtonGroup()
{
	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
	m_NowButtonIndex = MyMath::Vec2DInt(0, 0);

	m_ScrollPosMax = MyMath::Vec2DInt(0, 0);
	m_ScrollPosMin = MyMath::Vec2DInt(0, 0);

	m_CursorState = CURSOR_NONE;
	m_PrevCursorState = CURSOR_NONE;

	m_XFixed = false;
	m_YFixed = false;
	m_IsCursorMovable = false;

	m_CursorMoveTimer = 0;

	for (int i = 0; i < UI_BUTTON_MAX_NUM; i++)
	{
		m_UIButton[i] = nullptr;
	}
}

ButtonGroup::~ButtonGroup()
{
	Fin();
}

void ButtonGroup::Init()
{

}

void ButtonGroup::Start()
{
	m_NowButtonIndex = MyMath::Vec2DInt(1, 1);

	m_IsCursorMovable = true;
	UIManager* uiManager = UIManager::GetInstance();

	switch (m_Type)
	{
	case GROUP_HOME:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_BATTLE, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_OPTION, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
		m_TotalButtonIndex = MyMath::Vec2DInt(2, 1);
		break;

	case GROUP_BOSS_SELECT:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_PLAYER, MyMath::Vec2D(500.0f, 400.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_CPU1, MyMath::Vec2D(1100.0f, 400.0f), MyMath::Vec2DInt(2, 1));
		m_UIButton[2] = uiManager->CreateUIButton(UI_BUTTON_CPU2, MyMath::Vec2D(500.0f, 700.0f), MyMath::Vec2DInt(1, 2));
		m_UIButton[3] = uiManager->CreateUIButton(UI_BUTTON_CPU3, MyMath::Vec2D(1100.0f, 700.0f), MyMath::Vec2DInt(2, 2));
		m_TotalButtonIndex = MyMath::Vec2DInt(2, 2);
		break;

	case GROUP_MAP_SELECT:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_TEST_MAP, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_FACTORY, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
		m_UIButton[2] = uiManager->CreateUIButton(UI_BUTTON_FOREST, MyMath::Vec2D(1700.0f, 600.0f), MyMath::Vec2DInt(3, 1));
		m_TotalButtonIndex = MyMath::Vec2DInt(3, 1);
		break;

	case GROUP_CHARACTER_SELECT_BOSS:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_ROBOT, MyMath::Vec2D(300.0f, 500.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_BEAST, MyMath::Vec2D(300.0f, 500.0f), MyMath::Vec2DInt(1, 2));
		m_TotalButtonIndex = MyMath::Vec2DInt(1, 2);
		break;

	case GROUP_CHARACTER_SELECT_CHALLENGER:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_KNIGHT, MyMath::Vec2D(300.0f, 500.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_NINJA, MyMath::Vec2D(300.0f, 500.0f), MyMath::Vec2DInt(1, 2));
		m_UIButton[2] = uiManager->CreateUIButton(UI_BUTTON_FAIRY, MyMath::Vec2D(300.0f, 500.0f), MyMath::Vec2DInt(1, 3));
		m_TotalButtonIndex = MyMath::Vec2DInt(1, 3);
		break;

	case GROUP_RESULT:
		m_UIButton[0] = uiManager->CreateUIButton(UI_BUTTON_ONE_MORE_BATTLE, MyMath::Vec2D(500.0f, 750.0f), MyMath::Vec2DInt(1, 1));
		m_UIButton[1] = uiManager->CreateUIButton(UI_BUTTON_TO_HOME, MyMath::Vec2D(1100.0f, 750.0f), MyMath::Vec2DInt(2, 1));
		m_TotalButtonIndex = MyMath::Vec2DInt(2, 1);
		break;
	case GROUP_TYPE_MAX:
		break;
	case GROUP_TYPE_NONE:
		break;
	default:
		break;
	}

	int totalButtonNum = m_TotalButtonIndex.x * m_TotalButtonIndex.y;

	for (int i = 0; i < totalButtonNum; i++)
	{
		if (m_UIButton[i] != nullptr)
		{
			m_UIButtonList.push_back(m_UIButton[i]);
		}
	}
}

void ButtonGroup::Step()
{
	m_PrevCursorState = m_CursorState;
	m_CursorState = CURSOR_NONE;

	// âEì¸óÕ
	if ((Input::GetLeftStickX() >= 500 || Input::IsTriggerKey(Input::KEY_RIGHT)))
	{
		m_CursorState = CURSOR_RIGHT;
	}
	// ç∂ì¸óÕ
	if ((Input::GetLeftStickX() <= -500 || Input::IsTriggerKey(Input::KEY_LEFT)))
	{
		m_CursorState = CURSOR_LEFT;
	}
	// â∫ì¸óÕ
	if ((Input::GetLeftStickY() >= 500 || Input::IsTriggerKey(Input::KEY_DOWN)))
	{
		m_CursorState = CURSOR_DOWN;
	}
	// è„ì¸óÕ
	if ((Input::GetLeftStickY() <= -500 || Input::IsTriggerKey(Input::KEY_UP)))
	{
		m_CursorState = CURSOR_UP;
	}

	Sound* sound = SoundManager::GetInstance()->GetSound();

	if (m_IsCursorMovable || m_CursorState != m_PrevCursorState)
	{
		// âEà⁄ìÆ
		if (m_CursorState == CURSOR_RIGHT
			&& m_NowButtonIndex.x < m_TotalButtonIndex.x)
		{
			if (!m_XFixed)
			{
				m_NowButtonIndex.x++;
				sound->PlaySE(SE_CURSOR_MOVE);
				m_IsCursorMovable = false;
				m_CursorMoveTimer = 0;
			}
		}
		// ç∂à⁄ìÆ
		if (m_CursorState == CURSOR_LEFT
			&& m_NowButtonIndex.x > 1)
		{
			if (!m_XFixed)
			{
				m_NowButtonIndex.x--;
				sound->PlaySE(SE_CURSOR_MOVE);
				m_IsCursorMovable = false;
				m_CursorMoveTimer = 0;
			}
		}
		// â∫à⁄ìÆ
		if (m_CursorState == CURSOR_DOWN
			&& m_NowButtonIndex.y < m_TotalButtonIndex.y)
		{
			if (!m_YFixed)
			{
				m_NowButtonIndex.y++;
				sound->PlaySE(SE_CURSOR_MOVE);
				m_IsCursorMovable = false;
				m_CursorMoveTimer = 0;
			}
		}
		// è„à⁄ìÆ
		if (m_CursorState == CURSOR_UP
			&& m_NowButtonIndex.y > 1)
		{
			if (!m_YFixed)
			{
				m_NowButtonIndex.y--;
				sound->PlaySE(SE_CURSOR_MOVE);
				m_IsCursorMovable = false;
				m_CursorMoveTimer = 0;
			}
		}
	}

	for (auto& button : m_UIButtonList)
	{
		MyMath::VECTOR_INT thisIndex = button->GetIndex();
		if (thisIndex.x == m_NowButtonIndex.x && thisIndex.y == m_NowButtonIndex.y)
		{
			button->SetSelect(true);
		}
	}
}

void ButtonGroup::Update()
{
	if (!m_IsCursorMovable)
	{
		m_CursorMoveTimer++;

		if (m_CursorMoveTimer > CURSOR_MOVE_INTERVAL)
		{
			m_IsCursorMovable = true;
			m_CursorMoveTimer = 0;
		}
	}
}

void ButtonGroup::Fin()
{
	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
}

void ButtonGroup::RandomSelect()
{
	int resultX = GetRand(m_TotalButtonIndex.x - 1) + 1;
	int resultY = GetRand(m_TotalButtonIndex.y - 1) + 1;

	m_NowButtonIndex = MyMath::Vec2DInt(resultX, resultY);
}

void ButtonGroup::UIButtonScroll(VECTOR diff)
{
	for (auto& button : m_UIButtonList)
	{
		VECTOR currentPos = button->GetPos();

		VECTOR destPos = VAdd(currentPos, diff);

		button->SetPos(destPos);
	}
}

UIName ButtonGroup::GetSelectedName()
{
	for (auto& button : m_UIButtonList)
	{
		if (button->IsSelected())
		{
			return button->GetName();
		}
	}

	return UI_NAME_NONE;
}