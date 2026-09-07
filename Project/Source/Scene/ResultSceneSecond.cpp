#include "DxLib.h"
#include "ResultSceneSecond.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../Camera/CameraManager.h"
#include "../UI/UIManager.h"
#include "../Cursor/CursorManager.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

const VECTOR PARENT_POS = VGet(-20.0f, 0.0f, 0.0f);
const VECTOR CHILD_POS = VGet(0.0f, 0.0f, 0.0f);
const VECTOR CAMERA_TARGET = VGet(0.0f, 5.0f, 0.0f);
const VECTOR CAMERA_POS = VGet(0.0f, 8.0f, -35.0f);
const VECTOR UI_ONE_MORE_BATTLE_POS = VGet(500.0f, 750.0f, 0.0f);
const VECTOR UI_TO_HOME_POS = VGet(1100.0f, 750.0f, 0.0f);
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

	//CursorManager::CreateInstance();
	//CursorManager::GetInstance()->Init();
}

void ResultSceneSecond::Load()
{
	CameraManager::GetInstance()->Load();
	//CursorManager::GetInstance()->Load();
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
}

void ResultSceneSecond::Start()
{
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

	uiManager->CreateUIButton(UI_BUTTON_ONE_MORE_BATTLE, UI_ONE_MORE_BATTLE_POS, MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_TO_HOME, UI_TO_HOME_POS, MyMath::Vec2DInt(2, 1));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 1));
}

void ResultSceneSecond::Step()
{
	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CURSOR_SELECT);
		}

		m_SceneChangeStart = true;
	}

	//CameraManager::GetInstance()->Step();

	CharacterManager::GetInstance()->Step();

	UIManager::GetInstance()->Step();

	//CursorManager::GetInstance()->Step();
}

void ResultSceneSecond::Update()
{
	SceneBase::Update();

	CameraManager::GetInstance()->Update();

	CharacterManager::GetInstance()->Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	if (m_SceneChangeEnd)
	{
		switch (uiManager->GetSelectedName())
		{
		case UI_BUTTON_TO_HOME:
		{
			SceneManager::GetInstance()->ChangeScene(HOME);
			break;
		}
		case UI_BUTTON_ONE_MORE_BATTLE:
		{
			SceneManager::GetInstance()->ChangeScene(BOSS_SELECT);
			break;
		}
		default:
			break;
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

	//CursorManager::GetInstance()->Draw();
}

void ResultSceneSecond::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	CharacterManager::GetInstance()->Fin();

	UIManager::GetInstance()->ResetUI();

	//CursorManager::DeleteInstance();

	DeleteGraph(m_BGHandle);

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_RESULT);
}