#include "UIManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UIText.h"
#include "ButtonGroup.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Scene/SceneManager.h"
#include "../Component/Component.h"
#include "../Component/GameObject.h"

UIManager* UIManager::m_Instance = nullptr;

UIManager::UIManager()
{
	for (int i = 0; i < UI_TYPE_MAX; i++)
	{
		m_UI[i] = nullptr;
	}

	for (int i = 0; i < FONT_HANDLE_MAX; i++)
	{
		m_FontHandle[i] = 0;
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
	m_FontHandle[TIMER_TEXT] = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 40, -1);
	m_FontHandle[NAME_BATTLE_SCENE] = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 42, -1);
	m_FontHandle[NAME_RESULT_SCENE] = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 84, -1);
	m_FontHandle[MISSION_TEXT] = CreateFontToHandle("HGS‘n‰pŠpÎß¯Ìß‘Ì", 30, -1);

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

std::shared_ptr<GameObject> UIManager::CreateUIImage(UIName name, VECTOR pos, const char* filePath)
{
	auto uiImage = std::make_shared<GameObject>();

	//auto transform = uiImage->AddComponent<Transform>();
	auto spriteRenderer = uiImage->AddComponent<SpriteRenderer>(filePath);

	//transform->SetPos(pos);

	return uiImage;
}

UIButton* UIManager::CreateUIButton(UIName name, VECTOR pos, MyMath::VECTOR_INT index)
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

	return button;
}

UIText* UIManager::CreateUIText(const char* text, VECTOR pos, unsigned int color, FontHandleType type)
{
	UIText* newText = new UIText;

	newText->SetPos(pos);
	newText->SetColor(color);
	newText->SetFontType(type);

	newText->Init();
	newText->SetType(UI_TEXT);
	newText->Load();
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

	for (auto& buttonGroup : m_ButtonGroupList)
	{
		delete buttonGroup;
	}

	m_ButtonGroupList.clear();

	for (auto ui : m_UI)
	{
		delete ui;
	}
}

void UIManager::SetXFixed(bool fixed, ButtonGroupType type)
{
	ButtonGroup* buttonGroup = GetButtonGroup(type);

	buttonGroup->SetXFixed(fixed);
}

void UIManager::SetYFixed(bool fixed, ButtonGroupType type)
{
	ButtonGroup* buttonGroup = GetButtonGroup(type);

	buttonGroup->SetYFixed(fixed);
}

void UIManager::RandomSelect(ButtonGroupType type)
{
	GetButtonGroup(type)->RandomSelect();
}

void UIManager::SetGroupActive(bool active, ButtonGroupType type)
{
	ButtonGroup* buttonGroup = GetButtonGroup(type);

	buttonGroup->SetActive(active);
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
	ButtonGroup* buttonGroup = GetButtonGroup(type);

	if (buttonGroup != nullptr)
	{
		return buttonGroup->GetSelectedName();
	}

	return UI_NAME_NONE;
}

ButtonGroup* UIManager::GetButtonGroup(ButtonGroupType type)
{
	for (auto buttonGroup : m_ButtonGroupList)
	{
		if (buttonGroup->GetType() == type)
		{
			return buttonGroup;
		}
	}

	return nullptr;
}