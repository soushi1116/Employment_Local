#pragma once

class FPSSystem
{
public:
	static void Init();
	static void Update();
	static void Draw();

	static void WaitFPS();

	int GetDeltaTime() { return m_DeltaTime; }
	bool TakeOneMinute();

private:
	static int m_StartTime;
	static int m_Count;
	static float m_Fps;
	static int m_DeltaTime;
	static int m_PrevDeltaTime;
};

