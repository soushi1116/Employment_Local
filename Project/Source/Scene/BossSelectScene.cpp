#include "DxLib.h"
#include "BossSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
#include "../MyMath/MyMath.h"
#include <windows.h>
#include <string>

BossSelectScene::BossSelectScene() : SceneBase()
{

}

BossSelectScene::~BossSelectScene()
{

}

void BossSelectScene::Init()
{

}

void BossSelectScene::Load()
{

}

void BossSelectScene::Start()
{
	MissionManager::DeleteInstance();

	UIManager::GetInstance()->Start();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUIButton(UI_BUTTON_BOSS, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_PLAYER, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void BossSelectScene::Step()
{
	UIManager::GetInstance()->Step();

	SceneBase::Step();
}

void BossSelectScene::Update()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	SceneBase::Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_BOSS:
		{
			CharacterManager::GetInstance()->SetBossNum(0);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		case UI_BUTTON_PLAYER:
		{
			int random = GetRand(2) + 1;
			CharacterManager::GetInstance()->SetBossNum(3);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		default:
			break;
		}
	}

}

void BossSelectScene::Draw()
{
	UIManager::GetInstance()->Draw();
}

void BossSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}