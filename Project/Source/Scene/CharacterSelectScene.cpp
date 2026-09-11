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
#include "../Camera/CameraManager.h"
#include <string>

const int BOSS_NUM_MAX = 2;
const int BASTER_NUM_MAX = 3;

CharacterSelectScene::CharacterSelectScene() : SceneBase()
{
	m_IsBoss = false;
	m_SelectedNum = 0;
	m_MaxNum = 0;

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		m_CharaterData[i] = {0};
	}
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

	m_CharaterData[0].m_PanelHandle = LoadGraph("Data/UI/CharacterSelectScene/Robot.png");
	m_CharaterData[1].m_PanelHandle = LoadGraph("Data/UI/CharacterSelectScene/Beast.png");
}

void CharacterSelectScene::Start()
{
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f); // 画角を標準の60度にする
	SetCameraNearFar(1.0f, 1000.0f);                   // クリッピング距離をリセット

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	UIManager::GetInstance()->Start();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUIImage(UI_CHARACTER_SELECT, MyMath::Vec2D(800.0f, 100.0f));

	int bossNum = CharacterManager::GetInstance()->GetBossNum();

	if (bossNum == 0)
	{
		m_IsBoss = true;
	}

	CharacterManager* characterManager = CharacterManager::GetInstance();

	if (m_IsBoss)
	{
		m_MaxNum = BOSS_NUM_MAX;
		m_CharaterData[0].m_Character = characterManager->CreateCharacter(false, false, ROBOT);
		m_CharaterData[1].m_Character = characterManager->CreateCharacter(false, false, BEAST);
	}
	else
	{
		m_MaxNum = BASTER_NUM_MAX;
		m_CharaterData[0].m_Character = characterManager->CreateCharacter(false, false, KNIGHT);
		m_CharaterData[1].m_Character = characterManager->CreateCharacter(false, false, NINJA);
		m_CharaterData[2].m_Character = characterManager->CreateCharacter(false, false, FAIRY);
	}

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(FIXED_CAMERA);
	cameraManager->SetActiveCamera(FIXED_CAMERA);
	cameraManager->Start();
}

void CharacterSelectScene::Step()
{
	UIManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();

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

	if ((Input::GetLeftStickY() >= 500 || Input::IsTriggerKey(Input::KEY_DOWN)))
	{
		if (m_SelectedNum < m_MaxNum - 1)
		{
			m_SelectedNum++;
		}
	}
	if ((Input::GetLeftStickY() <= -500 || Input::IsTriggerKey(Input::KEY_UP)))
	{
		if (m_SelectedNum > 0)
		{
			m_SelectedNum--;
		}
	}
}

void CharacterSelectScene::Update()
{
	SceneBase::Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	CharacterManager* characterManager = CharacterManager::GetInstance();
	
	for (int i = 0; i < m_MaxNum; i++)
	{
		if (i == m_SelectedNum)
		{
			m_CharaterData[i].m_Character->SetActive(true);
			m_CharaterData[i].m_IsSelected = true;
		}
		else
		{
			m_CharaterData[i].m_Character->SetActive(false);
			m_CharaterData[i].m_IsSelected = false;
		}

		if (m_CharaterData[i].m_Character != nullptr)
		{
			m_CharaterData[i].m_Character->UpdateAnimation();
		}
	}

	characterManager->Update();

	CameraManager::GetInstance()->Update();

	if (m_SceneChangeEnd)
	{
		if (m_SceneBack)
		{
			SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
		}
		else
		{
			CharacterManager* characterManager = CharacterManager::GetInstance();

			int characterNum = 0;

			for (int i = 1; i < CHARACTER_MAX_NUM; i++)
			{
				// CPUのキャラクターをランダム選択
				if (characterManager->GetBossNum() == i)
				{
					characterNum = GetRand(BOSS_NUM_MAX - 1);

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
					characterNum = GetRand(BASTER_NUM_MAX - 1);

					switch (characterNum)
					{
					case 0:
						characterManager->SetCharacterType(i, KNIGHT);
						break;
					case 1:
						characterManager->SetCharacterType(i, NINJA);
						break;
					case 2:
						characterManager->SetCharacterType(i, FAIRY);
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
				SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
				characterManager->SetCharacterType(0, ROBOT);
				break;
			}
			case UI_BUTTON_BEAST:
			{
				SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
				characterManager->SetCharacterType(0, BEAST);
				break;
			}
			case UI_BUTTON_KNIGHT:
			{
				SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
				characterManager->SetCharacterType(0, KNIGHT);
				break;
			}
			case UI_BUTTON_NINJA:
			{
				SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
				characterManager->SetCharacterType(0, NINJA);
				break;
			}
			case UI_BUTTON_FAIRY:
			{
				SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
				characterManager->SetCharacterType(0, FAIRY);
				break;
			}
			default:
				break;
			}
		}
	}

}

void CharacterSelectScene::Draw()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	DrawGraph(0, 0, m_BGHandle, TRUE);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	CharacterManager::GetInstance()->DrawModel();
	CameraManager::GetInstance()->Draw();

	UIManager::GetInstance()->Draw();

	for (int i = 0; i < m_MaxNum; i++)
	{
		if (!m_CharaterData[i].m_IsSelected)
		{
			SetDrawBright(128, 128, 128);
		}
		DrawGraph(100, 600 + 150 * i, m_CharaterData[i].m_PanelHandle, TRUE);

		SetDrawBright(255, 255, 255);
	}
	
}

void CharacterSelectScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	UIManager::GetInstance()->ResetUI();
}