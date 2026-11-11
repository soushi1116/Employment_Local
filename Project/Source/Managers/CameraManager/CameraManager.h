#pragma once
#include <memory>
#include "../Singleton.h"
#include "../../Component/GameObject.h"
#include "../../Component/Component.h"

enum CameraType
{
	PLAYER_CAMERA,
	RESULT_CAMERA,
	DEBUG_CAMERA,
	FIXED_CAMERA,
	CAMERA_TYPE_MAX,
	CAMERA_TYPE_NONE = -1
};

class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	~CameraManager();

public:
	std::shared_ptr<GameObject> CreateCamera(CameraType type);
	void SetActiveCamera(CameraType type) { m_ActiveCamera = type; }

private:
	static CameraManager* m_Instance;

	CameraType m_ActiveCamera;
};
