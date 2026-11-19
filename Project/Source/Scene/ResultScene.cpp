#include "DxLib.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

const VECTOR BOSS_UI_RESULT_POS = MyMath::Vec2D(450.0f, 250.0f);
const VECTOR CHALLENGER_UI_RESULT_POS = MyMath::Vec2D(1150.0f, 250.0f);

const VECTOR RESULT_TEXT_POS = MyMath::Vec2D(800.0f, 100.0f);

const VECTOR TO_HOME_BUTTON_POS = MyMath::Vec2D(250.0f, 700.0f);
const VECTOR TO_NEXT_BATTLE_BUTTON_POS = MyMath::Vec2D(650.0f, 700.0f);

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
	SceneBase::Start();

	SoundManager::GetInstance()->GetSound()->PlayBGM(BGM_RESULT);

	CharacterManager* characterManager = CharacterManager::GetInstance();

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto resultGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_HOME);

	std::shared_ptr<UIButtonGroup> resultGroup = resultGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	Instantiate(bgObj);

	auto resultTextObj = rendererManager->CreateUIImage("Data/UI/ResultScene/ResultText.png", RESULT_TEXT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto buttonHomeObj = rendererManager->CreateUIButton("Data/UI/ResultScene/ToHome.png", TO_HOME_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), resultGroup);
	auto buttonNextBattleObj = rendererManager->CreateUIButton("Data/UI/ResultScene/OneMoreBattle.png", TO_NEXT_BATTLE_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 1), resultGroup);

	resultGroup->SetTotalIndex(MyMath::Vec2DInt(2, 1));

	resultGroup->SetActive(true);

	bool bossWin = BattleManager::GetInstance()->IsBossWin();
	bool challengerWin = BattleManager::GetInstance()->IsChallengerWin();

	VECTOR winTextPos = MyMath::VecZero();
	VECTOR loseTextPos = MyMath::VecZero();

	if (bossWin)
	{
		winTextPos = BOSS_UI_RESULT_POS;
		loseTextPos = CHALLENGER_UI_RESULT_POS;
	}
	else if (challengerWin)
	{
		winTextPos = CHALLENGER_UI_RESULT_POS;
		loseTextPos = BOSS_UI_RESULT_POS;
	}

	auto winTextObj = rendererManager->CreateUIImage("Data/UI/ResultScene/Result_Win.png", winTextPos, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto loseTextObj = rendererManager->CreateUIImage("Data/UI/ResultScene/Result_Lose.png", loseTextPos, VGet(1.0f, 1.0f, 1.0f), 0.0f);

	const auto& characterParams = CharacterManager::GetInstance()->GetParametersForResult();

	bool bossUICreated = false;

	for (auto& characterParam : characterParams)
	{
		auto characterUI = RendererManager::GetInstance()->CreateCharacterResultUI(characterParam, bossUICreated);

		if (characterParam->IsBoss()) bossUICreated = true;

		for (auto& ui : characterUI)
		{
			Instantiate(ui);
		}
	}

	Instantiate(resultGroupObj);
	Instantiate(resultTextObj);
	Instantiate(buttonHomeObj);
	Instantiate(buttonNextBattleObj);
	Instantiate(winTextObj);
	Instantiate(loseTextObj);
}

void ResultScene::Step()
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
}

void ResultScene::Update()
{
	SceneBase::Update();

	RendererManager* rendererManager = RendererManager::GetInstance();
	MyMath::VECTOR_INT currentIndex = rendererManager->GetCurrentIndex();

	if (m_SceneChangeEnd)
	{
		BattleManager* battleManager = BattleManager::GetInstance();

		SceneType nextScene = SCENE_TYPE_NONE;

		if (currentIndex.y == 1)
		{
			if (currentIndex.x == 1)
			{
				nextScene = HOME;
			}
			else if (currentIndex.x == 2)
			{
				nextScene = CHARACTER_SELECT;
			}
		}

		SoundManager::GetInstance()->GetSound()->StopBGM(BGM_RESULT);
		SceneManager::GetInstance()->ChangeScene(nextScene);
	}
}

void ResultScene::Draw()
{
	SceneBase::Draw();

}

void ResultScene::Fin()
{
	SceneBase::Fin();

	BattleManager::DeleteInstance();

	CharacterManager::GetInstance()->ClearCharacters();
}