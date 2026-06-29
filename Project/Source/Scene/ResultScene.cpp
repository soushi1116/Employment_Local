#include "DxLib.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"

ResultScene::ResultScene() : SceneBase()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{

}

void ResultScene::Load()
{

}

void ResultScene::Start()
{

}

void ResultScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void ResultScene::Update()
{

}

void ResultScene::Draw()
{
	if (CharacterManager::GetInstance()->WinnerIsParent())
	{
		DrawString(700, 400, "PARENT WIN!", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(700, 400, "CHILD WIN!", GetColor(255, 255, 255));
	}
}

void ResultScene::Fin()
{
	MissionManager::DeleteInstance();
}