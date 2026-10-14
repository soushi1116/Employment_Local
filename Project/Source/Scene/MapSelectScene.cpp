#include "DxLib.h"
#include "MapSelectScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Map/MapManager.h"

MapSelectScene::MapSelectScene() : SceneBase()
{

}

MapSelectScene::~MapSelectScene()
{

}

void MapSelectScene::Init()
{
	MapManager::CreateInstance();
}

void MapSelectScene::Load()
{
	
}

void MapSelectScene::Start()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	//uiManager->CreateUIImage(UI_MAP_SELECT, MyMath::Vec2D(800.0f, 100.0f));
	//uiManager->CreateUIImage(UI_RANDOM, MyMath::Vec2D(1300.0f, 200.0f));
	//uiManager->CreateUIImage(UI_BUTTON_Y, MyMath::Vec2D(1480.0f, 160.0f));

	uiManager->CreateUIButtonGroup(GROUP_MAP_SELECT);
}

void MapSelectScene::Step()
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

	// ランダムにマップを選択
	if (Input::IsTriggerButton(Input::BUTTON_Y))
	{
		UIManager::GetInstance()->RandomSelect(GROUP_MAP_SELECT);

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

void MapSelectScene::Update()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	SceneBase::Update();

	if (m_SceneChangeEnd)
	{
		if (m_SceneBack)
		{
			SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
		}
		else
		{
			switch (uiManager->GetSelectedName(GROUP_MAP_SELECT))
			{
			case UI_BUTTON_TEST_MAP:
			{
				//MapManager::GetInstance()->SetMapType(MAP_TEST);
				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->StopBGM(BGM_SELECT);
				SceneManager::GetInstance()->ChangeScene(BATTLE);
				break;
			}
			case UI_BUTTON_FACTORY:
			{
				//MapManager::GetInstance()->SetMapType(MAP_FACTORY);
				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->StopBGM(BGM_SELECT);
				SceneManager::GetInstance()->ChangeScene(BATTLE);
				break;
			}
			case UI_BUTTON_FOREST:
			{
				//MapManager::GetInstance()->SetMapType(MAP_FOREST);
				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->StopBGM(BGM_SELECT);
				SceneManager::GetInstance()->ChangeScene(BATTLE);
				break;
			}
			default:
				break;
			}
		}
	}

}

void MapSelectScene::Draw()
{
	UIManager::GetInstance()->Draw();
}

void MapSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}