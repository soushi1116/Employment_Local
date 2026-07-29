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
	m_SceneBack = false;
}

SceneBase::~SceneBase()
{

}

void SceneBase::Update()
{
	if (Event::ChangeScene(CHANGE_SCENE_INTERVAL))
	{
		m_SceneChangeEnd = true;

		Event::ResetCount();
	}
}