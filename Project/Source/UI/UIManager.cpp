#include "UIManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UIText.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UI[i] = nullptr;
	}

	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
	m_NowButtonIndex = MyMath::Vec2DInt(0, 0);

	m_XFixed = false;
	m_YFixed = false;
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
		ui->Load();
	}
}

void UIManager::Start()
{
	for (auto& ui : m_UIList)
	{
		ui->Start();
	}

	m_NowButtonIndex = MyMath::Vec2DInt(1, 1);
}

void UIManager::Step()
{
	for (auto& ui : m_UIList)
	{
		ui->Step();
	}

	Sound* sound = SoundManager::GetInstance()->GetSound();

	// âE
	if (Input::GetLeftStickX() >= 500 && m_NowButtonIndex.x < m_TotalButtonIndex.x)
	{
		if (!m_XFixed)
		{
			m_NowButtonIndex.x++;
			sound->PlaySE(SE_CURSOR_MOVE);
		}
	}
	// ç∂
	if (Input::GetLeftStickX() <= -500 && m_NowButtonIndex.x > 1)
	{
		if (!m_XFixed)
		{
			m_NowButtonIndex.x--;
			sound->PlaySE(SE_CURSOR_MOVE);
		}
	}
	// â∫
	if (Input::GetLeftStickY() >= 500 && m_NowButtonIndex.y < m_TotalButtonIndex.y)
	{
		if (!m_YFixed)
		{
			m_NowButtonIndex.y++;
			sound->PlaySE(SE_CURSOR_MOVE);
		}
	}
	// è„
	if (Input::GetLeftStickY() <= -500 && m_NowButtonIndex.y > 1)
	{
		if (!m_YFixed)
		{
			m_NowButtonIndex.y--;
			sound->PlaySE(SE_CURSOR_MOVE);
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
	image->Load();
	image->Start();
		
	m_UIList.push_back(image);
}

void UIManager::CreateUIButton(UIName name, VECTOR pos, MyMath::VECTOR_INT index)
{
	UIButton* button = new UIButton;

	button->SetPos(pos);

	button->Init();
	button->SetType(UI_BUTTON);
	button->SetName(name);
	button->SetIndex(index);
	button->Load();
	button->Start();

	m_UIList.push_back(button);
	m_UIButtonList.push_back(button);
}

void UIManager::CreateUIText(const char* text, VECTOR pos, unsigned int color)
{
	UIText* newText = new UIText;

	newText->SetPos(pos);
	newText->SetColor(color);

	newText->Init();
	newText->SetType(UI_TEXT);
	newText->Load();
	newText->SetText(text);
	newText->Start();

	m_UIList.push_back(newText);
}

void UIManager::DeleteUI(UIName name)
{
	for (auto& ui : m_UIList)
	{
		if (ui->GetName() == name)
		{
			delete ui;
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
