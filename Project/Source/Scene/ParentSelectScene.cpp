#include "DxLib.h"
#include "ParentSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"

ParentSelectScene::ParentSelectScene() : SceneBase()
{
	m_ParentHandle = 0;
	m_ChildHandle = 0;
	m_ParentSelected = false;
}

ParentSelectScene::~ParentSelectScene()
{

}

void ParentSelectScene::Init()
{

}

void ParentSelectScene::Load()
{
	m_ParentHandle = LoadGraph("Data/UI/ParentSelectScene/Parent.png");
	m_ChildHandle = LoadGraph("Data/UI/ParentSelectScene/Child.png");
}

void ParentSelectScene::Start()
{
	MissionManager::DeleteInstance();

	m_ParentSelected = true;

	/*CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->CreateCharacter(true);

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		characterManager->CreateCharacter(false);
	}*/
}

void ParentSelectScene::Step()
{
	if (Input::GetLeftStickX() >= 500)
	{
		m_ParentSelected = false;
	}
	if (Input::GetLeftStickX() <= -500)
	{
		m_ParentSelected = true;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (m_ParentSelected)
		{
			CharacterManager::GetInstance()->SetParentNum(0);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
		}
		else
		{
			int random = GetRand(2) + 1;
			CharacterManager::GetInstance()->SetParentNum(3);
			SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
		}
	}
}

void ParentSelectScene::Update()
{

}

void ParentSelectScene::Draw()
{
	if (m_ParentSelected)
	{
		DrawGraph(300, 400, m_ParentHandle, TRUE);
	}
	else
	{
		DrawGraph(1000, 400, m_ChildHandle, TRUE);
	}

	SetDrawBright(128, 128, 128);

	if (!m_ParentSelected)
	{
		DrawGraph(300, 400, m_ParentHandle, TRUE);
	}
	else
	{
		DrawGraph(1000, 400, m_ChildHandle, TRUE);
	}

	SetDrawBright(255, 255, 255);
}

void ParentSelectScene::Fin()
{

}