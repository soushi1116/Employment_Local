#include "DxLib.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"

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

	SetDrawScreen(DX_SCREEN_BACK);

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

	SceneManager::DeleteInstance();

	Input::Fin();

	DxLib_End();

	return 0;
}