#include "DxLib.h"
#include "BossSelectScene.h"
#include "SceneManager.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Component/AllComponents.h"
#include "../Managers/RendererManager/RendererManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include <windows.h>
#include <string>

const VECTOR BOSS_SELECT_TEXT_POS = MyMath::Vec2D(800.0f, 200.0f);
const VECTOR CHALLENGER_BUTTON_POS = MyMath::Vec2D(500.0f, 600.0f);
const VECTOR BOSS_BUTTON_POS = MyMath::Vec2D(1100.0f, 600.0f);

BossSelectScene::BossSelectScene() : SceneBase()
{

}

BossSelectScene::~BossSelectScene()
{

}

void BossSelectScene::Init()
{

}

void BossSelectScene::Load()
{
	
}

void BossSelectScene::Start()
{
	SceneBase::Start();

	BattleManager::CreateInstance();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_SELECT);

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto bossSelectGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_BOSS_SELECT);

	std::shared_ptr<UIButtonGroup> bossSelectGroup = bossSelectGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto bossSelectTextObj = rendererManager->CreateUIImage("Data/UI/BossSelectScene/BossSelect.png", BOSS_SELECT_TEXT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto buttonChallengerObj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/Challenger.png", CHALLENGER_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), bossSelectGroup);
	auto buttonBossObj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/Boss.png", BOSS_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 1), bossSelectGroup);

	bossSelectGroup->SetTotalIndex(MyMath::Vec2DInt(2, 1));

	Instantiate(bossSelectGroupObj);
	Instantiate(bgObj);
	Instantiate(bossSelectTextObj);
	Instantiate(buttonChallengerObj);
	Instantiate(buttonBossObj);

	bossSelectGroup->SetActive(true);
}

void BossSelectScene::Step()
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

void BossSelectScene::Update()
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
			BattleManager* battleManager = BattleManager::GetInstance();

			if (currentIndex.x == 1 && currentIndex.y == 1)
			{
				battleManager->SetBossMember(OPPONENT_1);
			}
			else
			{
				battleManager->SetBossMember(PLAYER);
			}

			SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
		}
	}

}

void BossSelectScene::Draw()
{
	SceneBase::Draw();
}

void BossSelectScene::Fin()
{
	SceneBase::Fin();
}