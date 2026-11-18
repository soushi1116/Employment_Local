#pragma once
#include "../Component.h"

class GameObject;
class Physics3D;
class CharacterInput;

class Camera : public Component
{
public:
	Camera(GameObject* owner);
	~Camera();

public:
	void Start() override;
	void Step() override;
	void Update() override;

public:
	void SetParent(std::shared_ptr<GameObject> parent) { m_ParentObject = parent; }

	void CollisionStage(int stageCollisionHandle);

	void SetStageCollsionHandle(int handle) { m_StageCollisionHandle = handle; }

	VECTOR GetRot() const { return m_RealRot; }

private:
	std::weak_ptr<Physics3D> m_Physics3D;
	std::weak_ptr<CharacterInput> m_Input;
	std::weak_ptr<GameObject> m_ParentObject;

	VECTOR m_Pos;
	VECTOR m_RealRot;
	VECTOR m_InputRot;
	VECTOR m_UpVec;
	VECTOR m_TargetPos;
	float m_AngleOffsetX;
	float m_DefaultAngleX;

	int m_StageCollisionHandle;

	bool m_MapInterrupt;
};

