#include "DxLib.h"
#include "Component/GameObject.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "Managers/CharacterManager/CharacterManager.h"
#include "Managers/CameraManager/CameraManager.h"
#include "FPS/FPSManager.h"
#include "Sound/SoundManager.h"
#include "Sound/Sound.h"
#include "Managers/RendererManager/RendererManager.h"
#include "Managers/AnimationManager/AnimationManager.h"
#include "Managers/InputManager/InputManager.h"
#include "Managers/EffectManager/EffectManager.h"
#include "EffekseerForDXLib.h"
#include "ShadowMap/ShadowMap.h"

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
	EffectManager::CreateInstance();
	EffectManager::GetInstance()->SetUp();

	SetDrawScreen(DX_SCREEN_BACK);

	RendererManager::CreateInstance();

	AnimationManager::CreateInstance();
	AnimationManager::GetInstance()->LoadAnimationData("Data/Parameters/AnimData.csv");

	// SoundManager生成、初期化、ロード
	SoundManager::CreateInstance();
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->CreateSound();
	Sound* sound = soundManager->GetSound();
	sound->LoadBGM();
	sound->LoadSE();

	// SoundManager生成、初期化、各カメラ生成
	CameraManager::CreateInstance();

	// CharacterManager生成
	CharacterManager::CreateInstance();

	// SceneManager生成、初期化
	SceneManager::CreateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	// ShadowMap生成
	ShadowMap::CreateInstance();

	// Input初期化
	Input::Init();

	// InputManager生成
	InputManager::CreateInstance();

	// FPSManager生成、初期化
	FPSManager::CreateInstance();
	FPSManager* fpsManager = FPSManager::GetInstance();
	fpsManager->Init();

	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		ClearDrawScreen();

		Input::Update();

		Effekseer_Sync3DSetting();

		sceneManager->Update();

		UpdateEffekseer3D();

		DrawEffekseer3D();

		fpsManager->Update();
		fpsManager->Draw();

		Input::Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		fpsManager->WaitFPS();

		ScreenFlip();
	}

	SoundManager::DeleteInstance();

	CharacterManager::DeleteInstance();

	SceneManager::DeleteInstance();

	Effkseer_End();

	EffectManager::DeleteInstance();

	CameraManager::DeleteInstance();

	Input::Fin();

	DxLib_End();

	return 0;
}