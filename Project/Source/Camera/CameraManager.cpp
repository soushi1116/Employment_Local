#include "CameraManager.h"
#include "Camera.h"
#include "ResultCamera.h"

CameraManager* CameraManager::m_Instance = nullptr;

CameraManager::CameraManager()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		m_Camera[i] = nullptr;
	}

	m_ActiveCamera = CAMERA_TYPE_NONE;
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
	case RESULT_CAMERA:
		if (m_Camera[RESULT_CAMERA] == nullptr)
		{
			m_Camera[RESULT_CAMERA] = new ResultCamera;
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
	switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Step();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Step();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}
}

void CameraManager::Update()
{
	switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Update();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Update();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}
}

void CameraManager::Draw()
{
	switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Draw();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Draw();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
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