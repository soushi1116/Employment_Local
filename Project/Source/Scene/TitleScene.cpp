#include "DxLib.h"
#include <math.h>
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../UI/UIManager.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Managers/RendererManager/RendererManager.h"

#include "../Component/GameObject.h"
#include "../Component/Component.h"

const float BLINK_SPEED = 0.05f;
const float PUSHED_BLINK_SPEED = 0.5f;

TitleScene::TitleScene() : SceneBase()
{
	m_Blink = 0.0f;
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

	VECTOR pressBPos = MyMath::Vec2D(500.0f, 600.0f);
	VECTOR bgPos = MyMath::Vec2D(800.0f, 450.0f);
	auto bg = RendererManager::GetInstance()->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto pressB = UIManager::GetInstance()->CreateUIImage(PRESS_B, pressBPos, "Data/UI/TitleScene/Press_B_Button.png");

	m_GameObjects.push_back(bg);
	m_GameObjects.push_back(pressB);
}

void TitleScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_GAME_START);
		}

		m_SceneChangeStart = true;
	}

	if (m_SceneChangeStart)
	{
		m_Blink += PUSHED_BLINK_SPEED;
	}
	else
	{
		m_Blink += BLINK_SPEED;
	}

	if (m_Blink > DX_TWO_PI_F)
	{
		m_Blink -= DX_TWO_PI_F;
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
	UIManager::GetInstance()->ResetUI();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_TITLE);
}