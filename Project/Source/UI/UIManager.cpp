#include "UIManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UIText.h"
#include "ButtonGroup.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Scene/SceneManager.h"

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

	for (auto& buttonGroup : m_ButtonGroupList)
	{
		buttonGroup->Init();
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

	for (auto& buttonGroup : m_ButtonGroupList)
	{
		buttonGroup->Start();
	}
}

void UIManager::Step()
{
	for (auto& ui : m_UIList)
	{
		ui->Step();
	}

	for (auto& buttonGroup : m_ButtonGroupList)
	{
		buttonGroup->Step();
	}
}

void UIManager::Update()
{
	for (auto& ui : m_UIList)
	{
		ui->Update();
	}

	for (auto& buttonGroup : m_ButtonGroupList)
	{
		buttonGroup->Update();
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

	for (auto& group : m_ButtonGroupList)
	{
		delete group;
	}

	m_ButtonGroupList.clear();

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

ButtonGroup* UIManager::CreateUIButtonGroup(ButtonGroupType type)
{
	ButtonGroup* group = new ButtonGroup;

	group->Init();
	group->SetType(type);
	group->Start();

	m_ButtonGroupList.push_back(group);

	return group;
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

	for (auto ui : m_UI)
	{
		delete ui;
	}
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

UIName UIManager::GetSelectedName(ButtonGroupType type)
{
	for (auto& buttonGroup : m_ButtonGroupList)
	{
		if (buttonGroup->GetType() == type)
		{
			return buttonGroup->GetSelectedName();
		}
	}

	return UI_NAME_NONE;
}