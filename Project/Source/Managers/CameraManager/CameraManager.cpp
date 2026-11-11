#include "CameraManager.h"
#include "../../Component/AllComponents.h"
#include "../../Scene/SceneBase.h"

CameraManager* CameraManager::m_Instance = nullptr;

CameraManager::CameraManager()
{
	m_ActiveCamera = CAMERA_TYPE_NONE;
}

CameraManager::~CameraManager()
{
	
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