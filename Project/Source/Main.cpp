#include "DxLib.h"
#include "Component/GameObject.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "MyEffekseer/EffekseerManager.h"
#include "Character/CharacterManager.h"
#include "UI/UIManager.h"
#include "Camera/CameraManager.h"
#include "FPS/FPSManager.h"
#include "Sound/SoundManager.h"
#include "Sound/Sound.h"
#include "Managers/RendererManager/RendererManager.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR IpCmdLine, _In_ int nShowCmd)
{
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetLightAmbColor(GetColorF(0.4f, 0.4f, 0.4f, 1.0f));

	// EffekseerManager生成、初期設定
	EffekseerManager::CreateInstance();
	EffekseerManager::GetInstance()->SetUp();

	SetDrawScreen(DX_SCREEN_BACK);

	// UIManager生成、初期化
	UIManager::CreateInstance();
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Init();
	uiManager->Load();

	RendererManager::CreateInstance();

	// SoundManager生成、初期化、ロード
	SoundManager::CreateInstance();
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->CreateSound();
	Sound* sound = soundManager->GetSound();
	sound->LoadBGM();
	sound->LoadSE();

	// SoundManager生成、初期化、各カメラ生成
	CameraManager::CreateInstance();
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(CAMERA);
	cameraManager->CreateCamera(RESULT_CAMERA);
	cameraManager->CreateCamera(DEBUG_CAMERA);
	cameraManager->Init();

	// CharacterManager生成
	CharacterManager::CreateInstance();

	// SceneManager生成、初期化
	SceneManager::CreateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	// Input初期化
	Input::Init();

	// FPSManager生成、初期化
	FPSManager::CreateInstance();
	FPSManager* fpsManager = FPSManager::GetInstance();
	fpsManager->Init();

	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		ClearDrawScreen();

		Input::Update();

		sceneManager->Update();

		fpsManager->Update();
		fpsManager->Draw();

		Input::Draw();

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