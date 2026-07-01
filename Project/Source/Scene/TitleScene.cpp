#include "DxLib.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"

TitleScene::TitleScene() : SceneBase()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	
}

void TitleScene::Load()
{

}

void TitleScene::Start()
{
	
}

void TitleScene::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void TitleScene::Update()
{
	
}

void TitleScene::Draw()
{
	DrawString(700, 400, "TITLE", GetColor(255, 255, 255));
	DrawString(700, 500, "B:START", GetColor(255, 255, 255));
}

void TitleScene::Fin()
{
	
}