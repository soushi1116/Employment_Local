#include "DxLib.h"
#include "HomeScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"

HomeScene::HomeScene() : SceneBase()
{

}

HomeScene::~HomeScene()
{

}

void HomeScene::Init()
{

}

void HomeScene::Load()
{

}

void HomeScene::Start()
{
	MissionManager::DeleteInstance();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();

	uiManager->CreateUIButton(UI_BUTTON_BATTLE, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_OPTION, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void HomeScene::Step()
{
	SceneBase::Step();

	UIManager::GetInstance()->Step();
}

void HomeScene::Update()
{
	SceneBase::Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_BATTLE:
		{
			SceneManager::GetInstance()->ChangeScene(PARENT_SELECT);
			break;
		}
		case UI_BUTTON_OPTION:
		{
			
			break;
		}
		default:
			break;
		}
	}
}

void HomeScene::Draw()
{
	UIManager::GetInstance()->Draw();
}

void HomeScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}