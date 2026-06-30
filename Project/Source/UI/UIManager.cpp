#include "UIManager.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UIImage[i] = nullptr;
	}
}

UIManager::~UIManager()
{

}

void UIManager::Init()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Init();
	}
}

void UIManager::Load()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Load();
	}
}

void UIManager::Start()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Start();
	}
}

void UIManager::Step()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Step();
	}
}

void UIManager::Update()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Update();
	}
}

void UIManager::Draw()
{
	for (auto& ui : m_UIImageList)
	{
		ui->Draw();
	}
}

void UIManager::Fin()
{
	for (auto& ui : m_UIImageList)
	{
		delete ui;
	}

	m_UIImageList.clear();

	for (auto ui : m_UIImage)
	{
		delete ui;
	}
}

void UIManager::CreateUI(UIType type, VECTOR pos)
{
	UIImage* ui = new UIImage;

	ui->Init();
	ui->SetPos(pos);
	ui->SetType(type);
	ui->Load();
	ui->Start();

	m_UIImageList.push_back(ui);
}

void UIManager::ResetUI()
{
	for (auto& ui : m_UIImageList)
	{
		delete ui;
	}

	m_UIImageList.clear();

	for (auto ui : m_UIImage)
	{
		delete ui;
	}
}
