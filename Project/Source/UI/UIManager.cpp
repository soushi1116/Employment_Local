#include "UIManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UIText.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"

UIManager* UIManager::m_Instance = nullptr;

const int CURSOR_MOVE_INTERVAL = 20;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UI[i] = nullptr;
	}

	m_CursorState = CURSOR_NONE;
	m_PrevCursorState = CURSOR_NONE;

	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
	m_NowButtonIndex = MyMath::Vec2DInt(0, 0);

	m_XFixed = false;
	m_YFixed = false;
	m_IsCursorMovable = false;

	m_CursorMoveTimer = 0;
}

UIManager::~UIManager()
{

}

void UIManager::Init()
{
	for (auto& ui : m_UIList)
	{
		ui->Init();
	}
}

void UIManager::Load()
{
	for (auto& ui : m_UIList)
	{
		ui->Load(0);
	}
}

void UIManager::Start()
{
	for (auto& ui : m_UIList)
	{
		ui->Start();
	}

	m_NowButtonIndex = MyMath::Vec2DInt(1, 1);

	m_IsCursorMovable = true;
}

void UIManager::Step()
{
	for (auto& ui : m_UIList)
	{
		ui->Step();
	}

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

void UIManager::Update()
{
	for (auto& ui : m_UIList)
	{
		ui->Update();
	}

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

void UIManager::Draw()
{
	for (auto& ui : m_UIList)
	{
		ui->Draw();
	}
}

void UIManager::Fin()
{
	for (auto& ui : m_UIList)
	{
		delete ui;
	}

	m_UIList.clear();

	for (auto ui : m_UI)
	{
		delete ui;
	}
}

void UIManager::CreateUIImage(UIName name, VECTOR pos)
{
	UIImage* image = new UIImage;

	image->SetPos(pos);

	image->Init();
	image->SetType(UI_IMAGE);
	image->SetName(name);
	image->Load(0);
	image->Start();
		
	m_UIList.push_back(image);
}

UIButton* UIManager::CreateUIButton(UIName name, VECTOR pos, MyMath::VECTOR_INT index)
{
	UIButton* button = new UIButton;

	button->SetPos(pos);

	button->Init();
	button->SetType(UI_BUTTON);
	button->SetName(name);
	button->SetIndex(index);
	button->Load(0);
	button->Start();

	m_UIList.push_back(button);
	m_UIButtonList.push_back(button);

	return button;
}

UIText* UIManager::CreateUIText(const char* text, VECTOR pos, unsigned int color, int scale)
{
	UIText* newText = new UIText;

	newText->SetPos(pos);
	newText->SetColor(color);

	newText->Init();
	newText->SetType(UI_TEXT);
	newText->Load(scale);
	newText->SetText(text);
	newText->Start();

	m_UIList.push_back(newText);

	return newText;
}

void UIManager::DeleteUI(UIBase* deleteUI)
{
	for (auto& ui : m_UIList)
	{
		if (ui == deleteUI)
		{
			delete ui;
			m_UIList.remove(ui);

			break;
		}
	}
}

void UIManager::ResetUI()
{
	for (auto& ui : m_UIList)
	{
		delete ui;
	}

	m_UIList.clear();

	m_UIButtonList.clear();

	for (auto ui : m_UI)
	{
		delete ui;
	}

	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
}

void UIManager::RandomSelect()
{
	int resultX = GetRand(m_TotalButtonIndex.x - 1) + 1;
	int resultY = GetRand(m_TotalButtonIndex.y - 1) + 1;

	m_NowButtonIndex = MyMath::Vec2DInt(resultX, resultY);
}

UIName UIManager::GetSelectedName()
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

UIBase* UIManager::GetUI(UIName name)
{
	for (auto& ui : m_UIList)
	{
		if (ui->GetName() == name)
		{
			return ui;
		}
	}
	return nullptr;
}
