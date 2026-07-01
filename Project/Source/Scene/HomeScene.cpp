#include "DxLib.h"
#include "HomeScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"

HomeScene::HomeScene() : SceneBase()
{

}

HomeScene::~HomeScene()
{

}

void HomeScene::Init()
{

}

void HomeScene::Load()
{

}

void HomeScene::Start()
{
	MissionManager::DeleteInstance();

}

void HomeScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		SceneManager::GetInstance()->ChangeScene(PARENT_SELECT);
	}
}

void HomeScene::Update()
{

}

void HomeScene::Draw()
{
	DrawString(700, 400, "B:BATTLE", GetColor(255, 255, 255));
}

void HomeScene::Fin()
{

}