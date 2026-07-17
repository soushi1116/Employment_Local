#include "DxLib.h"
#include "OptionScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../Camera/CameraManager.h"
#include "../UI/UIManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"

const VECTOR PARENT_POS = VGet(-30.0f, 0.0f, 0.0f);
const VECTOR CHILD_POS = VGet(0.0f, 0.0f, 0.0f);
const VECTOR CAMERA_TARGET = VGet(0.0f, 5.0f, 0.0f);
const VECTOR CAMERA_POS = VGet(0.0f, 8.0f, -35.0f);
const VECTOR PARENT_UI_RESULT_POS = VGet(450.0f, 100.0f, 0.0f);
const VECTOR CHILD_UI_RESULT_POS = VGet(1150.0f, 100.0f, 0.0f);
const float CHILD_POS_DIF = 10.0f;

OptionScene::OptionScene() : SceneBase()
{

}

OptionScene::~OptionScene()
{

}

void OptionScene::Init()
{

}

void OptionScene::Load()
{
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void OptionScene::Start()
{
	m_BButtonSEType = SE_CURSOR_SELECT;

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIButton(UI_BUTTON_SOUND, MyMath::Vec2D(500.0f, 300.0f), MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_MANUAL, MyMath::Vec2D(500.0f, 600.0f), MyMath::Vec2DInt(1, 2));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(1, 2));
}

void OptionScene::Step()
{
	//CameraManager::GetInstance()->Step();

	SceneBase::Step();

	UIManager::GetInstance()->Step();
}

void OptionScene::Update()
{
	SceneBase::Update();

	UIManager::GetInstance()->Update();

	if (m_SceneChangeEnd)
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void OptionScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	UIManager::GetInstance()->Draw();
}

void OptionScene::Fin()
{
	UIManager::GetInstance()->ResetUI();

	DeleteGraph(m_BGHandle);
}