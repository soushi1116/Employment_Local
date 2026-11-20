#include "DxLib.h"
#include <math.h>
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Managers/RendererManager/RendererManager.h"

#include "../Component/GameObject.h"
#include "../Component/Component.h"

constexpr int BLINK_SPEED = 5;
constexpr int PUSHED_BLINK_SPEED = 20;

const VECTOR TITLE_POS = MyMath::Vec2D(800.0f, 350.0f);
const VECTOR PRESS_B_POS = MyMath::Vec2D(800.0f, 700.0f);

TitleScene::TitleScene()
	: SceneBase()
	, m_Blink(0.0f)
{
	
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	m_GameObjects.clear();
}

void TitleScene::Load()
{
}

void TitleScene::Start()
{
	SceneBase::Start();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_TITLE);

	RendererManager* rendererManager = RendererManager::GetInstance();
	auto bg = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto title = rendererManager->CreateUIImage("Data/UI/TitleScene/TitleImage.png", TITLE_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto pressB = rendererManager->CreateUIImage("Data/UI/TitleScene/Press_B_Button.png", PRESS_B_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);

	Instantiate(bg);
	Instantiate(title);
	Instantiate(pressB);

	pressB->GetComponent<SpriteRenderer>()->BlinkStart(BLINK_SPEED, true);
}

void TitleScene::Step()
{
	if (m_UIInputCmp->IsTriggerUI(INPUT_SELECT))
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_GAME_START);
		}

		m_SceneChangeStart = true;

		for (auto& obj : m_GameObjects)
		{
			if (auto spriteRenderer = obj->GetComponent<SpriteRenderer>())
			{
				spriteRenderer->BlinkStart(PUSHED_BLINK_SPEED, true);
			}
		}
	}
}

void TitleScene::Update()
{
	SceneBase::Update();

	if (m_SceneChangeEnd)
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void TitleScene::Draw()
{
	SceneBase::Draw();
}

void TitleScene::Fin()
{
	SceneBase::Fin();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_TITLE);
}