#include "UIManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "../Input/Input.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UI[i] = nullptr;
	}

	m_TotalButtonIndex = MyMath::Vec2DInt(0, 0);
	m_NowButtonIndex = MyMath::Vec2DInt(0, 0);
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

	if (Input::GetLeftStickX() >= 500 && m_NowButtonIndex.x < m_TotalButtonIndex.x)
	{
		m_NowButtonIndex.x++;
	}
	if (Input::GetLeftStickX() <= -500 && m_NowButtonIndex.x > 1)
	{
		m_NowButtonIndex.x--;
	}
	if (Input::GetLeftStickY() >= 500 && m_NowButtonIndex.y < m_TotalButtonIndex.y)
	{
		m_NowButtonIndex.y--;
	}
	if (Input::GetLeftStickY() <= -500 && m_NowButtonIndex.y > 1)
	{
		m_NowButtonIndex.y++;
	}
}

void UIManager::Update()
{
	for (auto& ui : m_UIList)
	{
		ui->Update();
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

void UIManager::ResetUI()
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
