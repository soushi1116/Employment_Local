#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "DebugCamera.h"

const float CAMERA_NEAR_CLIP = 0.01f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float ROTATION_SPEED = 0.03f;
const float MOVE_SPEED = 0.1f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;

DebugCamera::DebugCamera()
{
	m_TargetCharacter = nullptr;
	m_Move = MyMath::VecZero();
}

DebugCamera::~DebugCamera()
{
	Fin();
}

void DebugCamera::Init()
{

}

void DebugCamera::Load()
{

}

void DebugCamera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_UpVec = VGet(0.0f, 1.0f, 0.0f);
}

void DebugCamera::Step()
{
	if (Input::IsInputKey(Input::KEY_A))
	{
		m_Rot.y += ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_D))
	{
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_W))
	{
		m_Rot.x += ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_S))
	{
		m_Rot.x -= ROTATION_SPEED;
	}

	m_Rot.y += ROTATION_SPEED * Input::GetRightStickX() / 1000;
	m_Rot.x += ROTATION_SPEED * Input::GetRightStickY() / 1000;

	m_Move.x += MOVE_SPEED * Input::GetLeftStickX() / 1000;
	m_Move.z += MOVE_SPEED * Input::GetLeftStickY() / 1000;

	if (m_Rot.x >= X_ROTATION_MAX)
	{
		m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Rot.x <= 0.0f)
	{
		m_Rot.x = 0.0f;
	}
}

void DebugCamera::Update()
{
	VECTOR playerPos = m_TargetCharacter->GetPos();

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

	m_Target = playerPos;
	m_Target.y += m_TargetCharacter->GetRadius() * 1.5f;

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void DebugCamera::Draw()
{
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "ÉJÉÅÉâÇÃç¿ïW[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void DebugCamera::Fin()
{

}