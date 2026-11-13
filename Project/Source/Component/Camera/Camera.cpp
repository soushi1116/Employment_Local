#include "../Component.h"
#include "../GameObject.h"
#include "Camera.h"
#include "../../MyColor/MyColor.h"
#include "../../Managers/MapManager/MapManager.h"

const float CAMERA_NEAR_CLIP = 1.0f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float PLAYER_DISTANCE = -50.0f;
const float CAMERA_ROTATION_SPEED = 0.03f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;
const float X_ROTATION_MIN = DX_PI_F * 0.05f;

Camera::Camera(GameObject* owner) : Component(owner)
{
	m_Pos = MyMath::VecZero();
	m_RealRot = MyMath::VecZero();
	m_InputRot = MyMath::VecZero();
	m_UpVec = MyMath::VecZero();
	m_TargetPos = MyMath::VecZero();

	m_AngleOffsetX = 0.0f;
	m_DefaultAngleX = 0.0f;
	m_StageCollisionHandle = 0;
}

Camera::~Camera()
{

}

void Camera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_Physics3D = m_Owner->GetComponent<Physics3D>();

	auto parentObjShared = m_ParentObject.lock();
	if (!parentObjShared) return;

	m_Input = parentObjShared->GetComponent<CharacterInput>();

	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	m_DefaultAngleX = DX_PI_F * 0.2f;

	auto mapObj = MapManager::GetInstance()->GetCurrentMap();

	if (auto mapObjShared = mapObj.lock())
	{
		m_StageCollisionHandle = mapObjShared->GetComponent<Physics3D>()->GetCollision<MeshCollision>()->GetCollisionHandle();
	}
}

void Camera::Step()
{
	auto inputShared = m_Input.lock();
	if (!inputShared) return;

	m_InputRot.y += CAMERA_ROTATION_SPEED * inputShared->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000;
	m_InputRot.x += CAMERA_ROTATION_SPEED * inputShared->GetInputBattle(INPUT_ANGLE_ROT_Y) / 1000;

	m_RealRot = m_InputRot;

	m_RealRot.x += m_DefaultAngleX;

	CollisionStage(m_StageCollisionHandle);

	m_RealRot.x += m_AngleOffsetX;

	if (m_RealRot.x >= X_ROTATION_MAX)
	{
		m_RealRot.x = X_ROTATION_MAX;
	}
	else if (m_RealRot.x <= X_ROTATION_MIN)
	{
		m_RealRot.x = X_ROTATION_MIN;
	}
}

void Camera::Update()
{
	auto parentObjShared = m_ParentObject.lock();
	auto physicsShared = m_Physics3D.lock();

	if (!parentObjShared || !physicsShared) return;

	VECTOR playerPos = parentObjShared->GetPos();

	VECTOR vecOrigin = MyMath::VecScale(playerPos, -1.0f);
	MATRIX playerOrigin = MyMath::MatTranslation(vecOrigin);

	float newDistance = PLAYER_DISTANCE;
	MATRIX distance = MyMath::MatTranslation(VGet(0.0f, 0.0f, newDistance));

	MATRIX pitch = MyMath::MatRotationPitch(m_RealRot.x);
	MATRIX yaw = MyMath::MatRotationYaw(m_RealRot.y);

	MATRIX matPlayerPos = MyMath::MatTranslation(playerPos);

	MATRIX cameraMat = MyMath::MatMult(matPlayerPos, yaw);
	cameraMat = MyMath::MatMult(cameraMat, pitch);
	cameraMat = MyMath::MatMult(cameraMat, distance);
	cameraMat = MyMath::MatMult(cameraMat, playerOrigin);

	m_Pos = MyMath::MatTransform(cameraMat, playerPos);

	m_TargetPos = playerPos;
	m_TargetPos.y += parentObjShared->GetScale().y * 1.5f / 2.0f;

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_TargetPos, m_UpVec);

	physicsShared->SetPos(m_Pos);
	physicsShared->SetRot(m_RealRot);
	if (physicsShared->GetScale().y <= 0.0f)
	{
		physicsShared->SetScale(MyMath::VecSame(5.0f));
	}
}

void Camera::CollisionStage(int stageCollisionHandle)
{
	auto physicsShared = m_Physics3D.lock();

	if (!physicsShared) return;

	VECTOR cameraPos = VAdd(m_Pos, MyMath::VecY(-5.0f));
	VECTOR targetPos = VAdd(m_TargetPos, MyMath::VecY(5.0f));

	DrawLine3D(targetPos, cameraPos, COLOR_BLUE);

	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(stageCollisionHandle, -1, targetPos, cameraPos);

	VECTOR targetToCamera = MyMath::VecZero(), targetToHit = MyMath::VecZero();

	if (hitPoly.HitFlag == 1 && hitPoly.Normal.y < 0.1f)
	{
		targetToCamera = MyMath::VecCreate(targetPos, cameraPos);
		targetToHit = MyMath::VecCreate(targetPos, hitPoly.HitPosition);

		m_AngleOffsetX = acosf(VSize(targetToHit) / VSize(targetToCamera));
	}
	else
	{
		m_AngleOffsetX = 0.0f;
	}
}