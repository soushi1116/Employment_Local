#include "DxLib.h"
#include "FPSManager.h"
#include "FPS.h"

FPSManager* FPSManager::m_Instance = nullptr;

FPSManager::FPSManager()
{
	m_FPS = nullptr;
}

FPSManager::~FPSManager()
{
	
}

void FPSManager::CreateFPS()
{
	FPSSystem* fps = new FPSSystem;
}

void FPSManager::Init()
{
	CreateFPS();

	m_FPS->Init();
}

void FPSManager::Update()
{
	m_FPS->Update();
}

void FPSManager::Draw()
{
	m_FPS->Draw();
}

void FPSManager::WaitFPS()
{
	m_FPS->WaitFPS();
}