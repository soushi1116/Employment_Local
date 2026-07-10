#include "DxLib.h"
#include <math.h>
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../FPS/FPSManager.h"

const float BLINK_SPEED = 0.05f;
const float PUSHED_BLINK_SPEED = 0.5f;
const int CHANGE_SCENE_INTERVAL = 5;

TitleScene::TitleScene() : SceneBase()
{
	m_PressBHandle = 0;
	m_Blink = 0.0f;
	m_ButtonBPushed = false;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	
}

void TitleScene::Load()
{
	m_PressBHandle = LoadGraph("Data/UI/TitleScene/Press_B_Button.png");
}

void TitleScene::Start()
{

}

void TitleScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (!m_ButtonBPushed)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			m_ChangeSceneTimer = fps->GetDeltaTime();
		}

		m_ButtonBPushed = true;
	}

	if (m_ButtonBPushed)
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
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
	int nowCount = fps->GetDeltaTime();

	if (nowCount - m_ChangeSceneTimer > CHANGE_SCENE_INTERVAL)
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void TitleScene::Draw()
{
	DrawString(700, 400, "TITLE", GetColor(255, 255, 255));

	int blinkPercent = (int)(255.0f * (-cosf(m_Blink) / 2 + 0.5f));

	if (blinkPercent < 0) blinkPercent = 0;
	if (blinkPercent > 255) blinkPercent = 255;

	SetDrawBright(blinkPercent, blinkPercent, blinkPercent);
	DrawGraph(500, 600, m_PressBHandle, TRUE);

	SetDrawBright(255, 255, 255);
}

void TitleScene::Fin()
{
	
}