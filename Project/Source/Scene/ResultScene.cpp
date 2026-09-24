#include "DxLib.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Character/Functions/ResultSceneUI.h"
#include "../UI/UIManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

const VECTOR PARENT_UI_RESULT_POS = VGet(450.0f, 100.0f, 0.0f);
const VECTOR CHILD_UI_RESULT_POS = VGet(1150.0f, 100.0f, 0.0f);

ResultScene::ResultScene() : SceneBase()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{
	ResultSceneUI::Init();
}

void ResultScene::Load()
{
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
	ResultSceneUI::Load();
}

void ResultScene::Start()
{
	SoundManager::GetInstance()->GetSound()->PlayBGM(BGM_RESULT);

	CharacterManager* characterManager = CharacterManager::GetInstance();
	CharacterBase* boss = characterManager->SearchBoss();

	auto characterList = characterManager->GetCharacterList();

	if (characterList.empty())
	{
		characterManager->CreateCharacter(true, false, KNIGHT);
		characterManager->CreateCharacter(false, false, ROBOT);
		characterManager->CreateCharacter(false, false, NINJA);
		characterManager->CreateCharacter(false, false, FAIRY);
		characterManager->SetBossNum(1);
		characterManager->SetWinnerBoss(true);

		characterManager->Start();
	}

	int index = 0;

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(false);
	}

	UIManager* uiManager = UIManager::GetInstance();
	if (characterManager->WinnerIsBoss())
	{
		uiManager->CreateUIImage(UI_RESULT_WIN, PARENT_UI_RESULT_POS);
		uiManager->CreateUIImage(UI_RESULT_LOSE, CHILD_UI_RESULT_POS);
	}
	else
	{
		uiManager->CreateUIImage(UI_RESULT_LOSE, PARENT_UI_RESULT_POS);
		uiManager->CreateUIImage(UI_RESULT_WIN, CHILD_UI_RESULT_POS);
	}

	uiManager->CreateUIButtonGroup(GROUP_RESULT);
}

void ResultScene::Step()
{
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

	CharacterManager::GetInstance()->Step();

	UIManager::GetInstance()->Step();
}

void ResultScene::Update()
{
	SceneBase::Update();

	CharacterManager::GetInstance()->Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName(GROUP_RESULT))
		{
		case UI_BUTTON_TO_HOME:
		{
			SceneManager::GetInstance()->ChangeScene(HOME);
			break;
		}
		case UI_BUTTON_ONE_MORE_BATTLE:
		{
			SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
			break;
		}
		default:
			break;
		}
	}
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (auto& character : characterList)
	{
		ResultSceneUI::DrawFrame(character);
	}

	UIManager::GetInstance()->Draw();
}

void ResultScene::Fin()
{
	UIManager::GetInstance()->ResetUI();

	CharacterManager::GetInstance()->Fin();

	SoundManager::GetInstance()->GetSound()->StopBGM(BGM_RESULT);

	DeleteGraph(m_BGHandle);
}