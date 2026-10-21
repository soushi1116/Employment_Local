#include "DxLib.h"
#include "HomeScene.h"
#include "SceneManager.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

#include "../Managers/RendererManager/RendererManager.h"

#include "../Component/GameObject.h"
#include "../Component/Component.h"

const VECTOR HOME_TEXT_POS = MyMath::Vec2D(800.0f, 200.0f);
const VECTOR BATTLE_BUTTON_POS = MyMath::Vec2D(500.0f, 600.0f);
const VECTOR OPTION_BUTTON_POS = MyMath::Vec2D(1100.0f, 600.0f);

HomeScene::HomeScene() : SceneBase()
{

}

HomeScene::~HomeScene()
{

}

void HomeScene::Init()
{
	m_GameObjects.clear();
}

void HomeScene::Load()
{
	
}

void HomeScene::Start()
{
	SceneBase::Start();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_HOME);

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto homeGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_HOME);

	UIButtonGroup* homeGroup = homeGroupObj->GetComponent<UIButtonGroup>().get();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto homeTextObj = rendererManager->CreateUIImage("Data/UI/HomeScene/Home.png", HOME_TEXT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto buttonBattleObj = rendererManager->CreateUIButton("Data/UI/HomeScene/Battle.png", BATTLE_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), homeGroup);
	auto buttonOptionObj = rendererManager->CreateUIButton("Data/UI/HomeScene/Option.png", OPTION_BUTTON_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 1), homeGroup);

	homeGroup->SetTotalIndex(MyMath::Vec2DInt(2, 1));

	Instantiate(homeGroupObj);
	Instantiate(bgObj);
	Instantiate(homeTextObj);
	Instantiate(buttonBattleObj);
	Instantiate(buttonOptionObj);

	homeGroup->SetActive(true);
}

void HomeScene::Step()
{
	RendererManager::GetInstance()->CheckCursor(m_UIInputCmp);

	if (m_UIInputCmp->IsTriggerUI(INPUT_SELECT))
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

void HomeScene::Update()
{
	SceneBase::Update();

	RendererManager* rendererManager = RendererManager::GetInstance();
	MyMath::VECTOR_INT currentIndex = rendererManager->GetCurrentIndex();

	if (m_SceneChangeEnd)
	{
		if (currentIndex.x == 1)
		{
			if (currentIndex.y == 1)
			{
				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->StopBGM(BGM_HOME);

				SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
			}
		}
		else if (currentIndex.x == 2)
		{
			if (currentIndex.y == 1)
			{
				SceneManager::GetInstance()->ChangeScene(OPTION);
			}
		}
	}
}

void HomeScene::Draw()
{
	SceneBase::Draw();

	//DrawGraph(0, 0, m_BGHandle, TRUE);
}

void HomeScene::Fin()
{
	SceneBase::Fin();
}