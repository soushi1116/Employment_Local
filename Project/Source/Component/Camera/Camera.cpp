#include "../Component.h"
#include "../GameObject.h"
#include "Camera.h"

const float CAMERA_NEAR_CLIP = 1.0f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float PLAYER_DISTANCE = -50.0f;
const float CAMERA_ROTATION_SPEED = 0.03f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;
const float X_ROTATION_MIN = DX_PI_F * 0.05f;

Camera::Camera(GameObject* owner) : Component(owner)
{
	m_Transform.m_Pos = MyMath::VecZero();
	m_Transform.m_Rot = MyMath::VecZero();
	m_Transform.m_UpVec = MyMath::VecZero();
	m_Transform.m_TargetPos = MyMath::VecZero();
}

Camera::~Camera()
{

}

void Camera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_Physics3D = m_Owner->GetComponent<Physics3D>();

	m_Input = m_ParentObject->GetComponent<CharacterInput>();

	m_Transform.m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	/*m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(MyMath::VecZero());
	m_Sphere->SetRadius(1.0f);*/

	m_Transform.m_Rot.x = DX_PI_F * 0.2f;
}

void Camera::Step()
{
	//if (Input::IsInputKey(Input::KEY_A))
	//{
	//	m_Rot.y += ROTATION_SPEED;
	//}
	//if (Input::IsInputKey(Input::KEY_D))
	//{
	//	m_Rot.y -= ROTATION_SPEED;
	//}
	//if (Input::IsInputKey(Input::KEY_W))
	//{
	//	m_Rot.x += ROTATION_SPEED;
	//}
	//if (Input::IsInputKey(Input::KEY_S))
	//{
	//	m_Rot.x -= ROTATION_SPEED;
	//}

	m_Transform.m_Rot.y += CAMERA_ROTATION_SPEED * m_Input->GetInputBattle(INPUT_ANGLE_ROT_X) / 1000;
	m_Transform.m_Rot.x += CAMERA_ROTATION_SPEED * m_Input->GetInputBattle(INPUT_ANGLE_ROT_Y) / 1000;

	if (m_Transform.m_Rot.x >= X_ROTATION_MAX)
	{
		m_Transform.m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Transform.m_Rot.x <= 0.0f)
	{
		m_Transform.m_Rot.x = 0.0f;
	}
}

void Camera::Update()
{
	VECTOR playerPos = m_ParentObject->GetPos();

	/*if (!m_HitStage)
	{
		VECTOR vecOrigin = MyMath::VecScale(playerPos, -1.0f);
		MATRIX playerOrigin = MyMath::MatTranslation(vecOrigin);

		MATRIX distance = MyMath::MatTranslation(VGet(0.0f, 0.0f, PLAYER_DISTANCE));

		MATRIX pitch = MyMath::MatRotationPitch(m_Rot.x);
		MATRIX yaw = MyMath::MatRotationYaw(m_Rot.y);

		MATRIX matPlayerPos = MyMath::MatTranslation(playerPos);

		MATRIX cameraMat = MyMath::MatMult(matPlayerPos, yaw);
		cameraMat = MyMath::MatMult(cameraMat, pitch);
		cameraMat = MyMath::MatMult(cameraMat, distance);
		cameraMat = MyMath::MatMult(cameraMat, playerOrigin);

		m_Pos = MyMath::MatTransform(cameraMat, playerPos);
	}*/

	VECTOR vecOrigin = MyMath::VecScale(playerPos, -1.0f);
	MATRIX playerOrigin = MyMath::MatTranslation(vecOrigin);

	MATRIX distance = MyMath::MatTranslation(VGet(0.0f, 0.0f, PLAYER_DISTANCE));

	MATRIX pitch = MyMath::MatRotationPitch(m_Transform.m_Rot.x);
	MATRIX yaw = MyMath::MatRotationYaw(m_Transform.m_Rot.y);

	MATRIX matPlayerPos = MyMath::MatTranslation(playerPos);

	MATRIX cameraMat = MyMath::MatMult(matPlayerPos, yaw);
	cameraMat = MyMath::MatMult(cameraMat, pitch);
	cameraMat = MyMath::MatMult(cameraMat, distance);
	cameraMat = MyMath::MatMult(cameraMat, playerOrigin);

	m_Transform.m_Pos = MyMath::MatTransform(cameraMat, playerPos);

	m_Transform.m_TargetPos = playerPos;
	m_Transform.m_TargetPos.y += m_ParentObject->GetScale().y * 1.5f / 2.0f;

	SetCameraPositionAndTargetAndUpVec(m_Transform.m_Pos, m_Transform.m_TargetPos, m_Transform.m_UpVec);
}