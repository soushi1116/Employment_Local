#include "DxLib.h"
#include "ResultSceneSecond.h"
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

ResultSceneSecond::ResultSceneSecond() : SceneBase()
{

}

ResultSceneSecond::~ResultSceneSecond()
{

}

void ResultSceneSecond::Init()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
}

void ResultSceneSecond::Load()
{
	CameraManager::GetInstance()->Load();
}

void ResultSceneSecond::Start()
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

void ResultSceneSecond::Step()
{
	//CameraManager::GetInstance()->Step();

	CharacterManager::GetInstance()->Step();

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		SceneManager::GetInstance()->ChangeScene(PARENT_SELECT);
	}

	if (Input::IsTriggerButton(Input::BUTTON_A))
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void ResultSceneSecond::Update()
{
	CameraManager::GetInstance()->Update();

	CharacterManager::GetInstance()->Update();
}

void ResultSceneSecond::Draw()
{
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetCameraPositionAndTarget_UpVecY(CAMERA_POS, CAMERA_TARGET);

	CameraManager::GetInstance()->Draw();

	DrawString(500, 700, "B:‚à‚¤ˆê“xí‚¤", GetColor(255, 255, 255));
	DrawString(1000, 700, "A:ƒz[ƒ€‰æ–Ê‚Ö", GetColor(255, 255, 255));

	CharacterManager::GetInstance()->DrawModel();
}

void ResultSceneSecond::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MissionManager::DeleteInstance();
	CharacterManager::GetInstance()->Fin();
}