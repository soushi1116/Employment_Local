#include "SceneBase.h"
#include "../Input/Input.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"

const int CHANGE_SCENE_INTERVAL = 2;

SceneBase* SceneBase::s_Instance = nullptr;

SceneBase::SceneBase()
{
	m_BGHandle = 0;
	m_SceneChangeStart = false;
	m_SceneChangeEnd = false;
	m_SceneBack = false;

	s_Instance = this;
}

SceneBase::~SceneBase()
{

}

void SceneBase::Start()
{
	for (auto go : m_GameObjects)
	{
		go->Start();
	}
}

void SceneBase::Update()
{
	for (auto go : m_GameObjects)
	{
		go->Update();
	}

	if (Event::ChangeScene(CHANGE_SCENE_INTERVAL))
	{
		m_SceneChangeEnd = true;

		Event::ResetCount();
	}
}

void SceneBase::Draw()
{
	for (auto go : m_GameObjects)
	{
		go->Draw();
	}
}
