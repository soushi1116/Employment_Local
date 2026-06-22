#include "DxLib.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "MyEffekseer/EffekseerManager.h"
#include "Character/CharacterManager.h"

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

	CharacterManager::CreateInstance();

	SceneManager::CreateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	Input::Init();

	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		ClearDrawScreen();

		Input::Update();

		sceneManager->Update();

		Input::Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
	}

	CharacterManager::DeleteInstance();

	SceneManager::DeleteInstance();

	EffekseerManager::DeleteInstance();

	Input::Fin();

	DxLib_End();

	return 0;
}