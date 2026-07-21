#include "DxLib.h"
#include "HomeScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

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
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void HomeScene::Start()
{
	MissionManager::DeleteInstance();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_HOME);

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIImage(UI_HOME, MyMath::Vec2D(800.0f, 200.0f));
	uiManager->CreateUIButton(UI_BUTTON_BATTLE, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_OPTION, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void HomeScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CURSOR_SELECT);
		}

		m_SceneChangeStart = true;
	}

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
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->StopBGM(BGM_HOME);

			SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
			break;
		}
		case UI_BUTTON_OPTION:
		{
			SceneManager::GetInstance()->ChangeScene(OPTION);
			break;
		}
		default:
			break;
		}
	}
}

void HomeScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	UIManager::GetInstance()->Draw();
}

void HomeScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}