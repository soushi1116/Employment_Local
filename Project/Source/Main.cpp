#include "DxLib.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "MyEffekseer/EffekseerManager.h"
#include "Character/CharacterManager.h"
#include "UI/UIManager.h"
#include "Camera/CameraManager.h"
#include "FPS/FPSManager.h"
#include "Sound/SoundManager.h"
#include "Sound/Sound.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 1.0f));

	EffekseerManager::CreateInstance();
	EffekseerManager::GetInstance()->SetUp();

	SetDrawScreen(DX_SCREEN_BACK);

	UIManager::CreateInstance();
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Init();

	SoundManager::CreateInstance();
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->CreateSound();
	Sound* sound = soundManager->GetSound();
	sound->LoadBGM();
	sound->LoadSE();

	CameraManager::CreateInstance();
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(CAMERA);
	cameraManager->CreateCamera(RESULT_CAMERA);
	cameraManager->CreateCamera(DEBUG_CAMERA);
	cameraManager->Init();

	CharacterManager::CreateInstance();

	SceneManager::CreateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	Input::Init();

	FPSManager::CreateInstance();
	FPSManager* fpsManager = FPSManager::GetInstance();
	fpsManager->Init();

	while (ProcessMessage() >= 0)
	{
		//Sleep(1);

		ClearDrawScreen();

		/*SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);*/

		Input::Update();

		sceneManager->Update();

		Input::Draw();

		fpsManager->Update();
		fpsManager->Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		fpsManager->WaitFPS();

		ScreenFlip();
	}

	CharacterManager::DeleteInstance();

	SceneManager::DeleteInstance();

	UIManager::DeleteInstance();

	EffekseerManager::DeleteInstance();

	CameraManager::DeleteInstance();

	Input::Fin();

	DxLib_End();

	return 0;
}