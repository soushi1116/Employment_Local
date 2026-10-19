#include "CameraManager.h"
#include "../Component/AllComponents.h"
#include "../Scene/SceneManager.h"

CameraManager* CameraManager::m_Instance = nullptr;

CameraManager::CameraManager()
{
	m_ActiveCamera = CAMERA_TYPE_NONE;
}

CameraManager::~CameraManager()
{
	Fin();
}

std::shared_ptr<GameObject> CameraManager::CreateCamera(CameraType type)
{
	auto obj = std::make_shared<GameObject>();
	obj->AddTag(TAG_CAMERA);

	obj->AddComponent<Physics3D>();

	switch (type)
	{
	case PLAYER_CAMERA:
	{
		auto camera = obj->AddComponent<Camera>();
		break;
	}
	case RESULT_CAMERA:
		break;
	case DEBUG_CAMERA:
		break;
	case FIXED_CAMERA:
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}

	return obj;
}

void CameraManager::Init()
{
	/*for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Init();
		}
	}*/
}

void CameraManager::Load()
{
	/*for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			camera->Load();
		}
	}*/
}

void CameraManager::Start()
{
	/*switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Start();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Start();
		break;
	case DEBUG_CAMERA:
		m_Camera[DEBUG_CAMERA]->Start();
		break;
	case FIXED_CAMERA:
		m_Camera[FIXED_CAMERA]->Start();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}*/
}

void CameraManager::Step()
{
	/*switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Step();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Step();
		break;
	case DEBUG_CAMERA:
		m_Camera[DEBUG_CAMERA]->Step();
		break;
	case FIXED_CAMERA:
		m_Camera[FIXED_CAMERA]->Step();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}*/
}

void CameraManager::Update()
{
	/*switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Update();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Update();
		break;
	case DEBUG_CAMERA:
		m_Camera[DEBUG_CAMERA]->Update();
		break;
	case FIXED_CAMERA:
		m_Camera[FIXED_CAMERA]->Update();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}*/
}

void CameraManager::Draw()
{
	/*switch (m_ActiveCamera)
	{
	case CAMERA:
		m_Camera[CAMERA]->Draw();
		break;
	case RESULT_CAMERA:
		m_Camera[RESULT_CAMERA]->Draw();
		break;
	case DEBUG_CAMERA:
		m_Camera[DEBUG_CAMERA]->Draw();
		break;
	case FIXED_CAMERA:
		m_Camera[FIXED_CAMERA]->Draw();
		break;
	case CAMERA_TYPE_MAX:
		break;
	case CAMERA_TYPE_NONE:
		break;
	default:
		break;
	}*/
}

void CameraManager::Fin()
{
	/*for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		CameraBase* camera = m_Camera[i];
		if (camera)
		{
			delete camera;
			m_Camera[i] = nullptr;
		}
	}*/
}