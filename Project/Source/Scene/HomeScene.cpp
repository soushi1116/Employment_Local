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

#include "../Managers/RendererManager/RendererManager.h"

#include "../Component/GameObject.h"
#include "../Component/Component.h"

HomeScene::HomeScene() : SceneBase()
{

}

HomeScene::~HomeScene()
{

}

void HomeScene::Init()
{
	m_GameObjects.clear();
}

void HomeScene::Load()
{
	
}

void HomeScene::Start()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_HOME);

	auto bg = RendererManager::GetInstance()->CreateBackGround("Data/BackGround/MissionSelectScene.png");

	m_GameObjects.push_back(bg);
}

void HomeScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B) || Input::IsTriggerKey(Input::KEY_Z))
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
		switch (uiManager->GetSelectedName(GROUP_HOME))
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
	SceneBase::Draw();

	DrawGraph(0, 0, m_BGHandle, TRUE);

	UIManager::GetInstance()->Draw();
}

void HomeScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}