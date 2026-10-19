#pragma once
#include <memory>
#include "../Component/GameObject.h"
#include "../Component/Component.h"

enum CameraType
{
	PLAYER_CAMERA,
	RESULT_CAMERA,
	DEBUG_CAMERA,
	FIXED_CAMERA,
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
	std::shared_ptr<GameObject> CreateCamera(CameraType type);
	void SetActiveCamera(CameraType type) { m_ActiveCamera = type; }

private:
	static CameraManager* m_Instance;

	CameraType m_ActiveCamera;
};
