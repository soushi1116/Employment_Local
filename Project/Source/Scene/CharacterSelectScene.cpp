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

const int BOSS_NUM_MAX = 1;
const int PLAYER_NUM_MAX = 1;

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
		uiManager->CreateUIButton(UI_BUTTON_ROBOT, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
		uiManager->CreateUIButton(UI_BUTTON_BEAST, MyMath::Vec2D(1000.0f, 600.0f), MyMath::Vec2DInt(2, 1));

		uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
	}
	else
	{
		uiManager->CreateUIButton(UI_BUTTON_KNIGHT, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 1));
		uiManager->CreateUIButton(UI_BUTTON_NINJA, MyMath::Vec2D(1000.0f, 600.0f), MyMath::Vec2DInt(2, 1));

		uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
	}
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
		CharacterManager* characterManager = CharacterManager::GetInstance();

		int characterNum = 0;

		for (int i = 1; i < CHARACTER_MAX_NUM; i++)
		{
			// CPUのキャラクターをランダム選択
			if (characterManager->GetBossNum() == i)
			{
				characterNum = GetRand(BOSS_NUM_MAX);

				switch (characterNum)
				{
				case 0:
					characterManager->SetCharacterType(i, ROBOT);
					break;
				case 1:
					characterManager->SetCharacterType(i, BEAST);
					break;
				default:
					break;
				}
			}
			else
			{
				characterNum = GetRand(PLAYER_NUM_MAX);

				switch (characterNum)
				{
				case 0:
					characterManager->SetCharacterType(i, KNIGHT);
					break;
				case 1:
					characterManager->SetCharacterType(i, NINJA);
					break;
				default:
					break;
				}
			}
		}
		
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_ROBOT:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			characterManager->SetCharacterType(0, ROBOT);
			break;
		}
		case UI_BUTTON_BEAST:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			characterManager->SetCharacterType(0, BEAST);
			break;
		}
		case UI_BUTTON_KNIGHT:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			characterManager->SetCharacterType(0, KNIGHT);
			break;
		}
		case UI_BUTTON_NINJA:
		{
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
			characterManager->SetCharacterType(0, NINJA);
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