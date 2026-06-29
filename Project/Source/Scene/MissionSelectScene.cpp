#include "DxLib.h"
#include "MissionSelectScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"

MissionSelectScene::MissionSelectScene() : SceneBase()
{

}

MissionSelectScene::~MissionSelectScene()
{

}

void MissionSelectScene::Init()
{
	MissionManager::CreateInstance();
	MissionManager* missionManager = MissionManager::GetInstance();
	missionManager->Init();
}

void MissionSelectScene::Load()
{
	MissionManager::GetInstance()->Load();
}

void MissionSelectScene::Start()
{
	MissionManager::GetInstance()->Start();
}

void MissionSelectScene::Step()
{
	MissionManager* missionManager = MissionManager::GetInstance();
	missionManager->Step();
	auto missionList = missionManager->GetMissionList();

	int index = 0;

	for (auto mission : missionList)
	{
		if (Input::IsTriggerButton(Input::BUTTON_B))
		{
			if (index == 0)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_A))
		{
			if (index == 1)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_Y))
		{
			if (index == 2)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_X))
		{
			if (index == 3)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);
			}
		}

		index++;
	}
}

void MissionSelectScene::Update()
{
	MissionManager::GetInstance()->Update();
}

void MissionSelectScene::Draw()
{
	MissionManager::GetInstance()->Draw();
}

void MissionSelectScene::Fin()
{
	//MissionManager::GetInstance()->Fin();
}