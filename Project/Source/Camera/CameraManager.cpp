#include "CameraManager.h"
#include "Camera.h"

CameraManager* CameraManager::m_Instance = nullptr;

CameraManager::CameraManager()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		m_Camera[i] = nullptr;
	}
}

CameraManager::~CameraManager()
{
	Fin();
}

void CameraManager::CreateCamera(CameraType type)
{
	switch (type)
	{
	case CAMERA:
		if (m_Camera[CAMERA] == nullptr)
		{
			m_Camera[CAMERA] = new Camera;
		}
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}
}

void CameraManager::Init()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Init();
		}
	}
}

void CameraManager::Load()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Load();
		}
	}
}

void CameraManager::Start()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Start();
		}
	}
}

void CameraManager::Step()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Step();
		}
	}
}

void CameraManager::Update()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Update();
		}
	}
}

void CameraManager::Draw()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Draw();
		}
	}
}

void CameraManager::Fin()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			delete camera;
			m_Camera[i] = nullptr;
		}
	}
}