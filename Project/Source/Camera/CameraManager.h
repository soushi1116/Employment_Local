#pragma once
#include "Camera.h"

enum CameraType
{
	CAMERA,
	CAMERA_TYPE_MAX,
	CAMERA_TYPE_NONE = -1
};

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
	void CreateCamera(CameraType type);
	Camera* GetCamera(CameraType type) { return m_Camera[type]; }

private:
	static CameraManager* m_Instance;

	Camera* m_Camera[CAMERA_TYPE_MAX];
};
