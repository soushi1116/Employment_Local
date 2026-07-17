#include "DxLib.h"
#include "MissionSelectScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../UI/UIManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"

const VECTOR UI_BUTTON_POS = VGet(200.0f, 100.0f, 0.0f);
const float UI_BUTTON_DIFF = 200.0f;

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
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void MissionSelectScene::Start()
{
	MissionManager::GetInstance()->Start();
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUIImage(UI_BUTTON_B, UI_BUTTON_POS);
	uiManager->CreateUIImage(UI_BUTTON_A, VGet(UI_BUTTON_POS.x + UI_BUTTON_DIFF, UI_BUTTON_POS.y + UI_BUTTON_DIFF, UI_BUTTON_POS.z));
	uiManager->CreateUIImage(UI_BUTTON_Y, VGet(UI_BUTTON_POS.x + UI_BUTTON_DIFF * 2, UI_BUTTON_POS.y + UI_BUTTON_DIFF * 2, UI_BUTTON_POS.z));
	uiManager->CreateUIImage(UI_BUTTON_X, VGet(UI_BUTTON_POS.x + UI_BUTTON_DIFF * 3, UI_BUTTON_POS.y + UI_BUTTON_DIFF * 3, UI_BUTTON_POS.z));
}

void MissionSelectScene::Step()
{
	MissionManager* missionManager = MissionManager::GetInstance();
	//missionManager->Step();
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

				m_SceneChangeStart = true;

				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->PlaySE(SE_MISSION_SELECT);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_A))
		{
			if (index == 1)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);

				m_SceneChangeStart = true;

				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->PlaySE(SE_MISSION_SELECT);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_Y))
		{
			if (index == 2)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);

				m_SceneChangeStart = true;

				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->PlaySE(SE_MISSION_SELECT);
			}
		}
		if (Input::IsTriggerButton(Input::BUTTON_X))
		{
			if (index == 3)
			{
				mission->SetSelected();
				SceneManager::GetInstance()->ChangeScene(BATTLE);

				m_SceneChangeStart = true;

				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->PlaySE(SE_MISSION_SELECT);
			}
		}

		index++;
	}
}

void MissionSelectScene::Update()
{
	SceneBase::Update();
	//MissionManager::GetInstance()->Update();
}

void MissionSelectScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);
	MissionManager::GetInstance()->Draw();
	UIManager::GetInstance()->Draw();
}

void MissionSelectScene::Fin()
{
	UIManager::GetInstance()->ResetUI();
	DeleteGraph(m_BGHandle);

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_SELECT);
}