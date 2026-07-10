#include "UIManager.h"
#include "UIBase.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UI[i] = nullptr;
	}
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
}

void UIManager::Step()
{
	for (auto& ui : m_UIList)
	{
		ui->Step();
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

void UIManager::CreateUI(UIType type, VECTOR pos)
{
	UIBase* ui = new UIBase;

	ui->Init();
	ui->SetPos(pos);
	ui->SetType(type);
	ui->Load();
	ui->Start();

	m_UIList.push_back(ui);
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
