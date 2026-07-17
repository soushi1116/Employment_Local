#include "DxLib.h"
#include "ResultScene.h"
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

ResultScene::ResultScene() : SceneBase()
{

}

ResultScene::~ResultScene()
{

}

void ResultScene::Init()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void ResultScene::Load()
{
	CameraManager::GetInstance()->Load();
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void ResultScene::Start()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_RESULT);

	m_BButtonSEType = SE_CURSOR_SELECT;

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->SetActiveCamera(RESULT_CAMERA);
	cameraManager->Start();

	CharacterBase* boss = CharacterManager::GetInstance()->SearchBoss();

	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	int index = 0;

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(false);

		character->SetRot(VGet(0.0f, 0.0f, 0.0f));

		if (character->IsBoss())
		{
			character->SetPos(PARENT_POS);
		}
		else
		{
			character->SetPos(VGet(CHILD_POS.x + CHILD_POS_DIF * index, CHILD_POS.y, CHILD_POS.z));
			index++;
		}
	}

	if (boss != nullptr)
	{
		CameraBase* camera = cameraManager->GetCamera(RESULT_CAMERA);
		camera->SetTargetCharacter(boss);
		camera->Update();
	}

	UIManager* uiManager = UIManager::GetInstance();
	if (CharacterManager::GetInstance()->WinnerIsBoss())
	{
		uiManager->CreateUIImage(UI_RESULT_WIN, PARENT_UI_RESULT_POS);
		uiManager->CreateUIImage(UI_RESULT_LOSE, CHILD_UI_RESULT_POS);
	}
	else
	{
		uiManager->CreateUIImage(UI_RESULT_LOSE, PARENT_UI_RESULT_POS);
		uiManager->CreateUIImage(UI_RESULT_WIN, CHILD_UI_RESULT_POS);
	}
}

void ResultScene::Step()
{
	//CameraManager::GetInstance()->Step();

	SceneBase::Step();

	CharacterManager::GetInstance()->Step();
}

void ResultScene::Update()
{
	SceneBase::Update();

	CameraManager::GetInstance()->Update();

	CharacterManager::GetInstance()->Update();

	if (m_SceneChangeEnd)
	{
		SceneManager::GetInstance()->ChangeScene(RESULT_SECOND);
	}
}

void ResultScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetCameraPositionAndTarget_UpVecY(CAMERA_POS, CAMERA_TARGET);

	CameraManager::GetInstance()->Draw();

	auto missionList = MissionManager::GetInstance()->GetMissionList();

	for (auto mission : missionList)
	{
		if (mission->IsSelected())
		{
			DrawRotaGraph(800, 750, 0.5, 0.0, mission->GetHandle(), TRUE);
		}
	}

	CharacterManager::GetInstance()->DrawModel();

	UIManager::GetInstance()->Draw();
}

void ResultScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MissionManager::DeleteInstance();

	UIManager::GetInstance()->ResetUI();

	DeleteGraph(m_BGHandle);
}