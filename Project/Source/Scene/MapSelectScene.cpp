#include "DxLib.h"
#include "MapSelectScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
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
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void MapSelectScene::Start()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIImage(UI_BOSS_SELECT, MyMath::Vec2D(800.0f, 100.0f));
	uiManager->CreateUIImage(UI_RANDOM, MyMath::Vec2D(1300.0f, 200.0f));
	uiManager->CreateUIImage(UI_BUTTON_Y, MyMath::Vec2D(1480.0f, 160.0f));

	uiManager->CreateUIButton(UI_BUTTON_TEST_MAP, MyMath::Vec2D(500.0f, 400.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_FACTORY, MyMath::Vec2D(1100.0f, 400.0f), MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
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
			switch (uiManager->GetSelectedName())
			{
			case UI_BUTTON_TEST_MAP:
			{
				MapManager::GetInstance()->SetMapType(MAP_TEST);
				SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
				break;
			}
			case UI_BUTTON_FACTORY:
			{
				MapManager::GetInstance()->SetMapType(MAP_FACTORY);
				SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
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
	DrawGraph(0, 0, m_BGHandle, TRUE);

	UIManager::GetInstance()->Draw();
}

void MapSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}