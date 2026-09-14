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
const int CURSOR_MOVE_INTERVAL = 20;
const VECTOR PANEL_DEFAULT_POS = MyMath::Vec2D(300.0f, 500.0f);

CharacterSelectScene::CharacterSelectScene() : SceneBase()
{
	m_IsBoss = false;
	m_SelectedNum = 0;
	m_MaxNum = 0;
	m_CursorMoveTimer = 0;

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
}

void CharacterSelectScene::Start()
{
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	SetCameraNearFar(1.0f, 1000.0f);

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

		m_CharaterData[0].m_PanelUI = uiManager->CreateUIButton(UI_BUTTON_ROBOT, PANEL_DEFAULT_POS, MyMath::Vec2DInt(1, 1));
		m_CharaterData[1].m_PanelUI = uiManager->CreateUIButton(UI_BUTTON_BEAST, PANEL_DEFAULT_POS, MyMath::Vec2DInt(1, 2));
	}
	else
	{
		m_MaxNum = BASTER_NUM_MAX;
		m_CharaterData[0].m_Character = characterManager->CreateCharacter(false, false, KNIGHT);
		m_CharaterData[1].m_Character = characterManager->CreateCharacter(false, false, NINJA);
		m_CharaterData[2].m_Character = characterManager->CreateCharacter(false, false, FAIRY);

		m_CharaterData[0].m_PanelUI = uiManager->CreateUIButton(UI_BUTTON_KNIGHT, PANEL_DEFAULT_POS, MyMath::Vec2DInt(1, 1));
		m_CharaterData[1].m_PanelUI = uiManager->CreateUIButton(UI_BUTTON_NINJA, PANEL_DEFAULT_POS, MyMath::Vec2DInt(1, 2));
		m_CharaterData[2].m_PanelUI = uiManager->CreateUIButton(UI_BUTTON_FAIRY, PANEL_DEFAULT_POS, MyMath::Vec2DInt(1, 3));
	}

	for (int i = 0; i < m_MaxNum; i++)
	{
		VECTOR panelPos = m_CharaterData[i].m_PanelUI->GetPos();
		m_CharaterData[i].m_PanelUI->SetPos(VAdd(panelPos, MyMath::Vec2D(30.0f * (float)i, 150.0f * (float)i)));
	}

	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(1, m_MaxNum));

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(FIXED_CAMERA);
	cameraManager->SetActiveCamera(FIXED_CAMERA);
	cameraManager->Start();

	m_CursorMoveTimer = CURSOR_MOVE_INTERVAL;
}

void CharacterSelectScene::Step()
{
	UIManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();

	m_CursorMoveTimer--;

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
}

void CharacterSelectScene::Update()
{
	SceneBase::Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	CharacterManager* characterManager = CharacterManager::GetInstance();
	
	for (int i = 0; i < m_MaxNum; i++)
	{
		if (m_CharaterData[i].m_PanelUI->IsSelected())
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
}

void CharacterSelectScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	CharacterManager::GetInstance()->DeleteCharacter();

	UIManager::GetInstance()->ResetUI();
}