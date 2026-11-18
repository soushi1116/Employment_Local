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

const VECTOR BOSS_SELECT_TEXT_POS = MyMath::Vec2D(800.0f, 150.0f);
const VECTOR PLAYER_BUTTON_POS = MyMath::Vec2D(500.0f, 400.0f);
const VECTOR CPU1_BUTTON_POS = MyMath::Vec2D(1000.0f, 400.0f);
const VECTOR CPU2_BUTTON_POS = MyMath::Vec2D(500.0f, 700.0f);
const VECTOR CPU3_BUTTON_POS = MyMath::Vec2D(1000.0f, 700.0f);

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

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_SELECT);

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto bossSelectGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_BOSS_SELECT);

	std::shared_ptr<UIButtonGroup> bossSelectGroup = bossSelectGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto bossSelectTextObj = rendererManager->CreateUIImage("Data/UI/BossSelectScene/BossSelect.png", BOSS_SELECT_TEXT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto buttonPlayerObj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/Player.png", PLAYER_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), bossSelectGroup);
	auto buttonCPU1Obj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/CPU1.png", CPU1_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 1), bossSelectGroup);
	auto buttonCPU2Obj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/CPU2.png", CPU2_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 2), bossSelectGroup);
	auto buttonCPU3Obj = rendererManager->CreateUIButton("Data/UI/BossSelectScene/CPU3.png", CPU3_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 2), bossSelectGroup);

	bossSelectGroup->SetTotalIndex(MyMath::Vec2DInt(2, 2));

	Instantiate(bossSelectGroupObj);
	Instantiate(bgObj);
	Instantiate(bossSelectTextObj);
	Instantiate(buttonPlayerObj);
	Instantiate(buttonCPU1Obj);
	Instantiate(buttonCPU2Obj);
	Instantiate(buttonCPU3Obj);

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
			SceneManager::GetInstance()->ChangeScene(HOME);
		}
		else
		{
			BattleManager* battleManager = BattleManager::GetInstance();

			if (currentIndex.x == 1 && currentIndex.y == 1)
			{
				battleManager->SetBossMember(PLAYER);
			}
			else if (currentIndex.x == 2 && currentIndex.y == 1)
			{
				battleManager->SetBossMember(OPPONENT_1);
			}
			else if (currentIndex.x == 1 && currentIndex.y == 2)
			{
				battleManager->SetBossMember(OPPONENT_2);
			}
			else if (currentIndex.x == 2 && currentIndex.y == 2)
			{
				battleManager->SetBossMember(OPPONENT_3);
			}

			SceneManager::GetInstance()->ChangeScene(MAP_SELECT);
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