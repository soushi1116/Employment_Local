#include "DxLib.h"
#include "CharacterSelectScene.h"
#include "SceneManager.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/RendererManager/RendererManager.h"
#include <string>

const int CHARACTER_NUM_MAX = 5;
const int CURSOR_MOVE_INTERVAL = 20;
const VECTOR PANEL_DEFAULT_POS = MyMath::Vec2D(300.0f, 500.0f);

const VECTOR KNIGHT_POS = MyMath::Vec2D(300.0f, 100.0f);
const VECTOR NINJA_POS = MyMath::Vec2D(300.0f, 250.0f);
const VECTOR FAIRY_POS = MyMath::Vec2D(300.0f, 400.0f);
const VECTOR ROBOT_POS = MyMath::Vec2D(300.0f, 550.0f);
const VECTOR BEAST_POS = MyMath::Vec2D(300.0f, 700.0f);


CharacterSelectScene::CharacterSelectScene() : SceneBase()
{
	m_IsBoss = false;
	m_SelectedNum = 0;
	m_MaxNum = 0;
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

	BattleManager::CreateInstance();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_SELECT);

	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	SetCameraNearFar(1.0f, 1000.0f);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	CharacterManager* characterManager = CharacterManager::GetInstance();

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto characterSelectGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_CHARACTER_SELECT);

	std::shared_ptr<UIButtonGroup> characterSelectGroup = characterSelectGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/CharacterSelectScene_Boss.png");
	auto knightButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Knight.png", KNIGHT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), characterSelectGroup);
	auto ninjaButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Ninja.png", NINJA_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 2), characterSelectGroup);
	auto fairyButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Fairy.png", FAIRY_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 3), characterSelectGroup);
	auto robotButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Robot.png", ROBOT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 4), characterSelectGroup);
	auto beastButtonObj = rendererManager->CreateUIButton("Data/UI/CharacterSelectScene/Beast.png", BEAST_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 5), characterSelectGroup);

	characterSelectGroup->SetTotalIndex(MyMath::Vec2DInt(1, 5));

	Instantiate(characterSelectGroupObj);
	Instantiate(bgObj);
	Instantiate(knightButtonObj);
	Instantiate(ninjaButtonObj);
	Instantiate(fairyButtonObj);
	Instantiate(robotButtonObj);
	Instantiate(beastButtonObj);

	characterSelectGroup->SetActive(true);

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(FIXED_CAMERA);
	cameraManager->SetActiveCamera(FIXED_CAMERA);
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
			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->StopBGM(BGM_SELECT);

			SceneManager::GetInstance()->ChangeScene(HOME);
		}
		else
		{
			CharacterManager* characterManager = CharacterManager::GetInstance();

			int characterNum = 0;

			for (int i = 1; i < CHARACTER_MAX_NUM; i++)
			{
				// CPUのキャラクターをランダム選択
				characterNum = GetRand(CHARACTER_NUM_MAX - 1);

				switch (characterNum)
				{
				case 0:
					characterManager->SetCharacterType(i, CharacterType::KNIGHT);
					break;
				case 1:
					characterManager->SetCharacterType(i, CharacterType::NINJA);
					break;
				case 2:
					characterManager->SetCharacterType(i, CharacterType::FAIRY);
					break;
				case 3:
					characterManager->SetCharacterType(i, CharacterType::ROBOT);
					break;
				case 4:
					characterManager->SetCharacterType(i, CharacterType::BEAST);
					break;
				default:
					break;
				}
			}

			RendererManager* rendererManager = RendererManager::GetInstance();
			MyMath::VECTOR_INT currentIndex = rendererManager->GetCurrentIndex();

			if (currentIndex.x == 1)
			{
				if (m_IsBoss)
				{
					if (currentIndex.y == 1)
					{
						characterManager->SetCharacterType(0, CharacterType::ROBOT);
					}
					else if (currentIndex.y == 2)
					{
						characterManager->SetCharacterType(0, CharacterType::BEAST);
					}
				}
				else
				{
					if (currentIndex.y == 1)
					{
						characterManager->SetCharacterType(0, CharacterType::KNIGHT);
					}
					else if (currentIndex.y == 2)
					{
						characterManager->SetCharacterType(0, CharacterType::NINJA);
					}
					else if (currentIndex.y == 3)
					{
						characterManager->SetCharacterType(0, CharacterType::FAIRY);
					}
				}
				SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
			}
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