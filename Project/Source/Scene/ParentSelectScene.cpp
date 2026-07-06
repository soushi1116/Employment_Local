#include "DxLib.h"
#include "ParentSelectScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"

ParentSelectScene::ParentSelectScene() : SceneBase()
{

}

ParentSelectScene::~ParentSelectScene()
{

}

void ParentSelectScene::Init()
{

}

void ParentSelectScene::Load()
{

}

void ParentSelectScene::Start()
{
	MissionManager::DeleteInstance();

	/*CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->CreateCharacter(true);

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		characterManager->CreateCharacter(false);
	}*/
}

void ParentSelectScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_RB))
	{
		int random = GetRand(2) + 1;
		CharacterManager::GetInstance()->SetParentNum(3);
		SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
	}
	if (Input::IsTriggerButton(Input::BUTTON_LB))
	{
		CharacterManager::GetInstance()->SetParentNum(0);
		SceneManager::GetInstance()->ChangeScene(MISSION_SELECT);
	}
}

void ParentSelectScene::Update()
{

}

void ParentSelectScene::Draw()
{
	DrawString(700, 400, "LB:PARENT RB:CHILD", GetColor(255, 255, 255));
}

void ParentSelectScene::Fin()
{

}