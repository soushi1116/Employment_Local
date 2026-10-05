#pragma once
#include "../Component.h"

class GameObject;
class _3DPhysics;
class CharacterInput;

class Camera : public Component
{
public:
	Camera(GameObject* owner);
	~Camera();

	void Start() override;
	void Step() override;
	void Update() override;

	void SetParent(std::shared_ptr<GameObject> parent) { m_ParentObject = parent; }

private:
	std::shared_ptr<_3DPhysics> m_3DPhysics;
	std::shared_ptr<CharacterInput> m_Input;
	std::shared_ptr<GameObject> m_ParentObject;

	struct CameraTransform
	{
		VECTOR m_Pos;
		VECTOR m_Rot;
		VECTOR m_UpVec;
		VECTOR m_TargetPos;
	};

	CameraTransform m_Transform;
};

