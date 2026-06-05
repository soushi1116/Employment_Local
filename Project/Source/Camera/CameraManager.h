#pragma once
#include "Camera.h"

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new CameraManager;
		}
	}

	static CameraManager* GetInstance() { return m_Instance; }

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
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void CreateCamera();
	CameraManager* GetCamera() { return m_Camera; }

private:
	static CameraManager* m_Instance;

	Camera* m_Camera;
};
