#include "DxLib.h"
#include "BossSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
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
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void BossSelectScene::Start()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_SELECT);

	MissionManager::DeleteInstance();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIImage(UI_BOSS_SELECT, MyMath::Vec2D(800.0f, 300.0f));
	uiManager->CreateUIButton(UI_BUTTON_BOSS, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_PLAYER, MyMath::Vec2D(1100.0f, 600.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void BossSelectScene::Step()
{
	UIManager::GetInstance()->Step();

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
			SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
			break;
		}
		case UI_BUTTON_PLAYER:
		{
			int random = GetRand(2) + 1;
			CharacterManager::GetInstance()->SetBossNum(random);
			SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
			break;
		}
		default:
			break;
		}
	}

}

void BossSelectScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	UIManager::GetInstance()->Draw();
}

void BossSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}