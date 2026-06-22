#include "DxLib.h"
#include "HomeScene.h"
#include "SceneManager.h"
#include "../Character/CharacterManager.h"
#include "../Input/Input.h"

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

}

void HomeScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_RB))
	{
		int random = GetRand(2) + 1;
		CharacterManager::GetInstance()->SetParentNum(3);
		SceneManager::GetInstance()->ChangeScene(BATTLE);
	}
	if (Input::IsTriggerButton(Input::BUTTON_LB))
	{
		CharacterManager::GetInstance()->SetParentNum(0);
		SceneManager::GetInstance()->ChangeScene(BATTLE);
	}
}

void HomeScene::Update()
{

}

void HomeScene::Draw()
{
	DrawString(700, 400, "LB:PARENT RB:CHILD", GetColor(255, 255, 255));
}

void HomeScene::Fin()
{

}