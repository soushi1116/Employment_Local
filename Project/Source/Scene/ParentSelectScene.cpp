#include "DxLib.h"
#include "ParentSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
#include "../MyMath/MyMath.h"
#include <windows.h>
#include <string>

ParentSelectScene::ParentSelectScene() : SceneBase()
{
	
}

ParentSelectScene::~ParentSelectScene()
{

}

void ParentSelectScene::Init()
{

}

void ParentSelectScene::Load()
{
	
}

void ParentSelectScene::Start()
{
	MissionManager::DeleteInstance();

	UIManager::GetInstance()->Start();

	/*CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->CreateCharacter(true);

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		characterManager->CreateCharacter(false);
	}*/

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUIButton(UI_BUTTON_PARENT, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_CHILD, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void ParentSelectScene::Step()
{
	UIManager::GetInstance()->Step();

	SceneBase::Step();
}

void ParentSelectScene::Update()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	SceneBase::Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_PARENT:
		{
			CharacterManager::GetInstance()->SetParentNum(0);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		case UI_BUTTON_CHILD:
		{
			int random = GetRand(2) + 1;
			CharacterManager::GetInstance()->SetParentNum(3);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		default:
			break;
		}
	}

}

void ParentSelectScene::Draw()
{
	UIManager::GetInstance()->Draw();
}

void ParentSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}