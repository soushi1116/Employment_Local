#include "DxLib.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../Camera/CameraManager.h"

const VECTOR PARENT_POS = VGet(-20.0f, 0.0f, 0.0f);
const VECTOR CHILD_POS = VGet(0.0f, 0.0f, 0.0f);
const VECTOR CAMERA_TARGET = VGet(0.0f, 5.0f, 0.0f);
const VECTOR CAMERA_POS = VGet(0.0f, 8.0f, -35.0f);
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
}

void ResultScene::Start()
{
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->Start();
	cameraManager->SetActiveCamera(RESULT_CAMERA);

	CharacterBase* player = CharacterManager::GetInstance()->GetCharacter(PLAYER);

	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	int index = 0;

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(false);

		character->SetRot(VGet(0.0f, 0.0f, 0.0f));

		if (character->IsParent())
		{
			character->SetPos(PARENT_POS);
		}
		else
		{
			character->SetPos(VGet(CHILD_POS.x + CHILD_POS_DIF * index, CHILD_POS.y, CHILD_POS.z));
			index++;
		}
	}

	if (player != nullptr)
	{
		CameraBase* camera = cameraManager->GetCamera(RESULT_CAMERA);
		camera->SetTargetCharacter(player);
		camera->Update();
	}
}

void ResultScene::Step()
{
	//CameraManager::GetInstance()->Step();

	CharacterManager::GetInstance()->Step();

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		SceneManager::GetInstance()->ChangeScene(RESULT_SECOND);
	}
}

void ResultScene::Update()
{
	CameraManager::GetInstance()->Update();

	CharacterManager::GetInstance()->Update();
}

void ResultScene::Draw()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetCameraPositionAndTarget_UpVecY(CAMERA_POS, CAMERA_TARGET);

	CameraManager::GetInstance()->Draw();

	if (CharacterManager::GetInstance()->WinnerIsParent())
	{
		DrawString(750, 300, "PARENT WIN!", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(750, 300, "CHILD WIN!", GetColor(255, 255, 255));
	}

	auto missionList = MissionManager::GetInstance()->GetMissionList();

	for (auto mission : missionList)
	{
		if (mission->IsSelected())
		{
			DrawRotaGraph(800, 700, 0.5, 0.0, mission->GetHandle(), TRUE);
		}
	}

	CharacterManager::GetInstance()->DrawModel();

}

void ResultScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MissionManager::DeleteInstance();
}