#include "DxLib.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
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
	
}

void ResultScene::Load()
{
	
}

void ResultScene::Start()
{
	SoundManager::GetInstance()->GetSound()->PlayBGM(BGM_RESULT);

	CharacterManager* characterManager = CharacterManager::GetInstance();
	/*CharacterBase* boss = characterManager->SearchBoss();

	auto characterList = characterManager->GetCharacterList();

	if (characterList.empty())
	{
		characterManager->CreateCharacter(true, false, CharacterType::KNIGHT);
		characterManager->CreateCharacter(false, false, CharacterType::ROBOT);
		characterManager->CreateCharacter(false, false, CharacterType::NINJA);
		characterManager->CreateCharacter(false, false, CharacterType::FAIRY);
		characterManager->SetBossNum(1);
		characterManager->SetWinnerBoss(true);

		characterManager->Start();
	}

	int index = 0;

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(false);
	}*/

	if (characterManager->WinnerIsBoss())
	{
		//uiManager->CreateUIImage(UI_RESULT_WIN, PARENT_UI_RESULT_POS);
		//uiManager->CreateUIImage(UI_RESULT_LOSE, CHILD_UI_RESULT_POS);
	}
	else
	{
		//uiManager->CreateUIImage(UI_RESULT_LOSE, PARENT_UI_RESULT_POS);
		//uiManager->CreateUIImage(UI_RESULT_WIN, CHILD_UI_RESULT_POS);
	}

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

}

void ResultScene::Update()
{
	SceneBase::Update();

	CharacterManager::GetInstance()->Update();

}

void ResultScene::Draw()
{
	/*const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (auto& character : characterList)
	{
		ResultSceneUI::DrawFrame(character);
	}*/

}

void ResultScene::Fin()
{

	CharacterManager::GetInstance()->Fin();

	SoundManager::GetInstance()->GetSound()->StopBGM(BGM_RESULT);
}