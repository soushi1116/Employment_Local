#include "DxLib.h"
#include "ResultSceneSecond.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../Camera/CameraManager.h"
#include "../UI/UIManager.h"
#include "../Cursor/CursorManager.h"

const VECTOR PARENT_POS = VGet(-20.0f, 0.0f, 0.0f);
const VECTOR CHILD_POS = VGet(0.0f, 0.0f, 0.0f);
const VECTOR CAMERA_TARGET = VGet(0.0f, 5.0f, 0.0f);
const VECTOR CAMERA_POS = VGet(0.0f, 8.0f, -35.0f);
const VECTOR UI_ONE_MORE_BATTLE_POS = VGet(450.0f, 700.0f, 0.0f);
const VECTOR UI_TO_HOME_POS = VGet(1150.0f, 700.0f, 0.0f);
const VECTOR PARENT_UI_RESULT_POS = VGet(450.0f, 150.0f, 0.0f);
const VECTOR CHILD_UI_RESULT_POS = VGet(1150.0f, 150.0f, 0.0f);
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

	CursorManager::CreateInstance();
	CursorManager::GetInstance()->Init();
}

void ResultSceneSecond::Load()
{
	CameraManager::GetInstance()->Load();
	CursorManager::GetInstance()->Load();
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void ResultSceneSecond::Start()
{
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->Start();
	cameraManager->SetActiveCamera(RESULT_CAMERA);

	float cursorMoveDiff = UI_TO_HOME_POS.x - UI_ONE_MORE_BATTLE_POS.x;
	CursorManager* cursorManager = CursorManager::GetInstance();
	cursorManager->CreateCursor(UI_ONE_MORE_BATTLE_POS, UI_TO_HOME_POS, UI_ONE_MORE_BATTLE_POS, 1.0f, cursorMoveDiff);
	cursorManager->Start();

	CharacterBase* player = CharacterManager::GetInstance()->SearchPlayer();

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

	UIManager* uiManager = UIManager::GetInstance();
	if (CharacterManager::GetInstance()->WinnerIsParent())
	{
		uiManager->CreateUI(UI_RESULT_WIN, PARENT_UI_RESULT_POS);
		uiManager->CreateUI(UI_RESULT_LOSE, CHILD_UI_RESULT_POS);
	}
	else
	{
		uiManager->CreateUI(UI_RESULT_LOSE, PARENT_UI_RESULT_POS);
		uiManager->CreateUI(UI_RESULT_WIN, CHILD_UI_RESULT_POS);
	}

	uiManager->CreateUI(UI_ONE_MORE_BATTLE, UI_ONE_MORE_BATTLE_POS);
	uiManager->CreateUI(UI_TO_HOME, UI_TO_HOME_POS);
}

void ResultSceneSecond::Step()
{
	//CameraManager::GetInstance()->Step();

	CharacterManager::GetInstance()->Step();

	CursorManager::GetInstance()->Step();
}

void ResultSceneSecond::Update()
{
	CameraManager::GetInstance()->Update();

	CharacterManager::GetInstance()->Update();

	CursorManager* cursorManager = CursorManager::GetInstance();
	cursorManager->Update();
	VECTOR cursorPos = cursorManager->GetCursor()->GetPos();

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (cursorPos.x == UI_ONE_MORE_BATTLE_POS.x && cursorPos.y == UI_ONE_MORE_BATTLE_POS.y)
		{
			SceneManager::GetInstance()->ChangeScene(PARENT_SELECT);
		}
		if (cursorPos.x == UI_TO_HOME_POS.x && cursorPos.y == UI_TO_HOME_POS.y)
		{
			SceneManager::GetInstance()->ChangeScene(HOME);
		}
	}
}

void ResultSceneSecond::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	SetCameraPositionAndTarget_UpVecY(CAMERA_POS, CAMERA_TARGET);

	CameraManager::GetInstance()->Draw();

	CharacterManager::GetInstance()->DrawModel();

	UIManager::GetInstance()->Draw();

	CursorManager::GetInstance()->Draw();
}

void ResultSceneSecond::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MissionManager::DeleteInstance();
	CharacterManager::GetInstance()->Fin();

	UIManager::GetInstance()->ResetUI();

	CursorManager::DeleteInstance();

	DeleteGraph(m_BGHandle);
}