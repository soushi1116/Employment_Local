#pragma once
#include "Dxlib.h"
#include "FPS.h"

class FPSSystem;

class FPSManager
{
public:
	FPSManager();
	~FPSManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new FPSManager;
		}
	}

	static FPSManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Update();
	void Draw();
	void WaitFPS();

	void CreateFPS();

	FPSSystem* GetFPS() { return m_FPS; }

private:
	static FPSManager* m_Instance;
	FPSSystem* m_FPS;
};

