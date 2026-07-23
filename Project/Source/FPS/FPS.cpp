#include "DxLib.h"
#include "FPS.h"

const int FPS_SAMPLE_NUM = 60;
const int FPS = 60;

int FPSSystem::m_StartTime = 0;
int FPSSystem::m_Count = 0;
float FPSSystem::m_Fps = 0;
int FPSSystem::m_DeltaTime = 0;
int FPSSystem::m_PrevDeltaTime = 0;

void FPSSystem::Init()
{
	m_StartTime = GetNowCount();
	m_Count = 0;
	m_Fps = 0.0f;
	m_DeltaTime = 0;
	m_PrevDeltaTime = 0;
}

void FPSSystem::Update()
{
	m_PrevDeltaTime = m_DeltaTime;

	if (m_Count == 0)
	{
		m_StartTime = GetNowCount();
	}

	if (m_Count == FPS_SAMPLE_NUM)
	{
		int time = GetNowCount();

		m_Fps = 1000.0f / ((time - m_StartTime) / (float)FPS_SAMPLE_NUM);
		m_Count = 0;
		m_DeltaTime++;
		m_StartTime = time;
	}
	m_Count++;
}

void FPSSystem::Draw()
{
	DrawFormatString(0, 880, GetColor(255, 255, 255), "FPSy%.1f, %dz", m_Fps, m_DeltaTime);
}

void FPSSystem::WaitFPS()
{
	int takeTime = GetNowCount() - m_StartTime;

	int waitTime = m_Count * 1000 / FPS - takeTime;

	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}

bool FPSSystem::TakeOneSecond()
{
	if (m_DeltaTime - m_PrevDeltaTime >= 1)
	{
		return true;
	}
	return false;
}
