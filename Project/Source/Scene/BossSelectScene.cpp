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

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIImage(UI_BOSS_SELECT, MyMath::Vec2D(800.0f, 100.0f));
	uiManager->CreateUIImage(UI_RANDOM, MyMath::Vec2D(1300.0f, 200.0f));
	uiManager->CreateUIImage(UI_BUTTON_Y, MyMath::Vec2D(1480.0f, 160.0f));

	uiManager->CreateUIButtonGroup(GROUP_BOSS_SELECT);
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

	if (Input::IsTriggerButton(Input::BUTTON_A))
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CANCEL);
		}

		m_SceneChangeStart = true;
		m_SceneBack = true;
	}

	// ランダムにボスを選択
	if (Input::IsTriggerButton(Input::BUTTON_Y))
	{
		UIManager::GetInstance()->RandomSelect();

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
		if (m_SceneBack)
		{
			SoundManager::GetInstance()->GetSound()->StopBGM(BGM_SELECT);

			SceneManager::GetInstance()->ChangeScene(HOME);
		}
		else
		{
			switch (uiManager->GetSelectedName(GROUP_BOSS_SELECT))
			{
			case UI_BUTTON_PLAYER:
			{
				CharacterManager::GetInstance()->SetBossNum(0);
				SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
				break;
			}
			case UI_BUTTON_CPU1:
			{
				CharacterManager::GetInstance()->SetBossNum(1);
				SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
				break;
			}
			case UI_BUTTON_CPU2:
			{
				CharacterManager::GetInstance()->SetBossNum(2);
				SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
				break;
			}
			case UI_BUTTON_CPU3:
			{
				CharacterManager::GetInstance()->SetBossNum(3);
				SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
				break;
			}
			default:
				break;
			}
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