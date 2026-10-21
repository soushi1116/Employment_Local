#include "DxLib.h"
#include "CharacterSelectScene.h"
#include "SceneManager.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../MyMath/MyMath.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"
#include "../Camera/CameraManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/RendererManager/RendererManager.h"
#include <string>

const int BOSS_NUM_MAX = 2;
const int BASTER_NUM_MAX = 3;
const int CURSOR_MOVE_INTERVAL = 20;
const VECTOR PANEL_DEFAULT_POS = MyMath::Vec2D(300.0f, 500.0f);

const VECTOR ROBOT_POS = MyMath::Vec2D(300.0f, 500.0f);
const VECTOR BEAST_POS = MyMath::Vec2D(300.0f, 700.0f);

const VECTOR KNIGHT_POS = MyMath::Vec2D(300.0f, 400.0f);
const VECTOR NINJA_POS = MyMath::Vec2D(300.0f, 600.0f);
const VECTOR FAIRY_POS = MyMath::Vec2D(300.0f, 800.0f);

CharacterSelectScene::CharacterSelectScene() : SceneBase()
{
	m_IsBoss = false;
	m_SelectedNum = 0;
	m_MaxNum = 0;
	m_CursorMoveTimer = 0;

}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Init()
{

}

void CharacterSelectScene::Load()
{
	
}

void CharacterSelectScene::Start()
{
	SceneBase::Start();

	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	SetCameraNearFar(1.0f, 1000.0f);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	Member bossMember = BattleManager::GetInstance()->GetBossMember();

	if (bossMember == PLAYER)
	{
		m_IsBoss = true;
	}

	CharacterManager* characterManager = CharacterManager::GetInstance();

	RendererManager* rendererManager = RendererManager::GetInstance();

	if (m_IsBoss)
	{
		auto charaSelcctBossGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_CHARACTER_SELECT_BOSS);

		UIButtonGroup* charaSelcctBossGroup = charaSelcctBossGroupObj->GetComponent<UIButtonGroup>().get();

		auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
		auto robotButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Robot.png", ROBOT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), charaSelcctBossGroup);
		auto beastButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Beast.png", BEAST_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 2), charaSelcctBossGroup);

		charaSelcctBossGroup->SetTotalIndex(MyMath::Vec2DInt(1, 2));

		Instantiate(charaSelcctBossGroupObj);
		Instantiate(bgObj);
		Instantiate(robotButtonObj);
		Instantiate(beastButtonObj);

		charaSelcctBossGroup->SetActive(true);
	}
	else
	{
		auto charaSelcctChallengerGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_CHARACTER_SELECT_CHALLENGER);

		UIButtonGroup* charaSelcctBossGroup = charaSelcctChallengerGroupObj->GetComponent<UIButtonGroup>().get();

		auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
		auto knightButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Knight.png", KNIGHT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), charaSelcctBossGroup);
		auto ninjaButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Ninja.png", NINJA_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 2), charaSelcctBossGroup);
		auto fairyButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Fairy.png", FAIRY_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 3), charaSelcctBossGroup);

		charaSelcctBossGroup->SetTotalIndex(MyMath::Vec2DInt(1, 3));

		Instantiate(charaSelcctChallengerGroupObj);
		Instantiate(bgObj);
		Instantiate(knightButtonObj);
		Instantiate(ninjaButtonObj);
		Instantiate(fairyButtonObj);

		charaSelcctBossGroup->SetActive(true);
	}

	//ButtonGroup* buttonGroup = nullptr;

	/*if (m_IsBoss)
	{
		m_MaxNum = BOSS_NUM_MAX;
		m_CharaterData[0].m_Character = characterManager->CreateCharacter(false, false, ROBOT);
		m_CharaterData[1].m_Character = characterManager->CreateCharacter(false, false, BEAST);

		buttonGroup = uiManager->CreateUIButtonGroup(GROUP_CHARACTER_SELECT_BOSS);
	}
	else
	{
		m_MaxNum = BASTER_NUM_MAX;
		m_CharaterData[0].m_Character = characterManager->CreateCharacter(false, false, KNIGHT);
		m_CharaterData[1].m_Character = characterManager->CreateCharacter(false, false, NINJA);
		m_CharaterData[2].m_Character = characterManager->CreateCharacter(false, false, FAIRY);

		buttonGroup = uiManager->CreateUIButtonGroup(GROUP_CHARACTER_SELECT_CHALLENGER);
	}*/

	//auto uiButtonList = buttonGroup->GetUIList();

	/*for (int i = 0; i < m_MaxNum; i++)
	{
		m_CharaterData[i].m_PanelUI = uiButtonList[i];

		VECTOR panelPos = m_CharaterData[i].m_PanelUI->GetPos();
		m_CharaterData[i].m_PanelUI->SetPos(VAdd(panelPos, MyMath::Vec2D(30.0f * (float)i, 150.0f * (float)i)));
	}*/

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(FIXED_CAMERA);
	cameraManager->SetActiveCamera(FIXED_CAMERA);
	cameraManager->Start();

	m_CursorMoveTimer = CURSOR_MOVE_INTERVAL;
}

void CharacterSelectScene::Step()
{
	RendererManager::GetInstance()->CheckCursor(m_UIInputCmp);

	if (m_UIInputCmp->IsTriggerUI(INPUT_SELECT))
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CURSOR_SELECT);
		}

		m_SceneChangeStart = true;
	}
	else if (m_UIInputCmp->IsTriggerUI(INPUT_CANCEL))
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CANCEL);

			m_SceneBack = true;
		}

		m_SceneChangeStart = true;
	}
}

void CharacterSelectScene::Update()
{
	SceneBase::Update();

	RendererManager* rendererManager = RendererManager::GetInstance();
	MyMath::VECTOR_INT currentIndex = rendererManager->GetCurrentIndex();

	if (m_SceneChangeEnd)
	{
		if (m_SceneBack)
		{
			SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
		}
		else
		{
			/*CharacterManager* characterManager = CharacterManager::GetInstance();

			int characterNum = 0;*/

			//for (int i = 1; i < CHARACTER_MAX_NUM; i++)
			//{
			//	// CPUのキャラクターをランダム選択
			//	if (characterManager->GetBossNum() == i)
			//	{
			//		characterNum = GetRand(BOSS_NUM_MAX - 1);

			//		switch (characterNum)
			//		{
			//		case 0:
			//			characterManager->SetCharacterType(i, ROBOT);
			//			break;
			//		case 1:
			//			characterManager->SetCharacterType(i, BEAST);
			//			break;
			//		default:
			//			break;
			//		}
			//	}
			//	else
			//	{
			//		characterNum = GetRand(BASTER_NUM_MAX - 1);

			//		switch (characterNum)
			//		{
			//		case 0:
			//			characterManager->SetCharacterType(i, KNIGHT);
			//			break;
			//		case 1:
			//			characterManager->SetCharacterType(i, NINJA);
			//			break;
			//		case 2:
			//			characterManager->SetCharacterType(i, FAIRY);
			//			break;
			//		default:
			//			break;
			//		}
			//	}
			//}

			/*UIName selectedName = UI_NAME_NONE;

			if (m_IsBoss)
			{
				selectedName = uiManager->GetSelectedName(GROUP_CHARACTER_SELECT_BOSS);
			}
			else
			{
				selectedName = uiManager->GetSelectedName(GROUP_CHARACTER_SELECT_CHALLENGER);
			}*/

			/*switch (selectedName)
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
			}*/
		}
	}
}

void CharacterSelectScene::Draw()
{
	SceneBase::Draw();

	/*SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	CharacterManager::GetInstance()->DrawModel();
	CameraManager::GetInstance()->Draw();*/
}

void CharacterSelectScene::Fin()
{
	SceneBase::Fin();

	/*SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	CharacterManager::GetInstance()->DeleteCharacter();

	UIManager::GetInstance()->ResetUI();*/
}