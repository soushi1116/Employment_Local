#include "DxLib.h"
#include "CharacterSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
#include "../MyMath/MyMath.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"
#include <string>

CharacterSelectScene::CharacterSelectScene() : SceneBase()
{
	m_IsBoss = false;
}

CharacterSelectScene::~CharacterSelectScene()
{

}

void CharacterSelectScene::Init()
{

}

void CharacterSelectScene::Load()
{
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void CharacterSelectScene::Start()
{
	MissionManager::DeleteInstance();

	UIManager::GetInstance()->Start();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUIImage(UI_CHARACTER_SELECT, MyMath::Vec2D(800.0f, 300.0f));

	int bossNum = CharacterManager::GetInstance()->GetBossNum();

	if (bossNum == 0)
	{
		m_IsBoss = true;
	}

	if (m_IsBoss)
	{
		uiManager->CreateUIButton(UI_BUTTON_BOT, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	}
	else
	{
		uiManager->CreateUIButton(UI_BUTTON_KNIGHT, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
	}
	
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(1, 1));
}

void CharacterSelectScene::Step()
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

void CharacterSelectScene::Update()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	SceneBase::Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_BOT:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		case UI_BUTTON_KNIGHT:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			break;
		}
		default:
			break;
		}
	}

}

void CharacterSelectScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	UIManager::GetInstance()->Draw();
}

void CharacterSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
}