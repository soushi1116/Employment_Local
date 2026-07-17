#include "SceneBase.h"
#include "../Input/Input.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"

const int CHANGE_SCENE_INTERVAL = 2;

SceneBase::SceneBase()
{
	m_BGHandle = 0;
	m_SceneChangeStart = false;
	m_SceneChangeEnd = false;
	m_BButtonSEType = SE_TYPE_NONE;
}

SceneBase::~SceneBase()
{

}

void SceneBase::Step()
{
	// シーン遷移の処理　各シーンに書いた方がいいかも
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(m_BButtonSEType);
		}

		m_SceneChangeStart = true;
	}
}

void SceneBase::Update()
{
	if (Event::ChangeScene(CHANGE_SCENE_INTERVAL))
	{
		m_SceneChangeEnd = true;

		Event::ResetCount();
	}
}