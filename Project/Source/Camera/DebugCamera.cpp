#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "DebugCamera.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include <math.h>

const float CAMERA_NEAR_CLIP = 0.01f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float ROTATION_SPEED = 0.03f;
const float MOVE_SPEED = 1.0f;
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

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(MyMath::VecZero());
	m_Sphere->SetRadius(1.0f);
}

void DebugCamera::Step()
{
	m_Move = MyMath::VecZero();

	m_Rot.y += ROTATION_SPEED * Input::GetRightStickX() / 1000.0f;
	m_Rot.x += ROTATION_SPEED * Input::GetRightStickY() / 1000.0f;

	if (m_Rot.x >= 1.48f) m_Rot.x = 1.48f;
	if (m_Rot.x <= -1.48f) m_Rot.x = -1.48f;

	float forwardInput = 0.0f;
	float strafeInput = 0.0f;

	forwardInput -= (float)Input::GetLeftStickY() / 1000.0f;
	strafeInput += (float)Input::GetLeftStickX() / 1000.0f;

	float sinY = sinf(m_Rot.y);
	float cosY = cosf(m_Rot.y);

	m_Move.x += sinY * forwardInput * MOVE_SPEED;
	m_Move.z += cosY * forwardInput * MOVE_SPEED;

	m_Move.x += cosY * strafeInput * MOVE_SPEED;
	m_Move.z -= sinY * strafeInput * MOVE_SPEED;

	if (Input::IsInputButton(Input::BUTTON_RB))
	{
		m_Pos.y++;
	}
	if (Input::IsInputButton(Input::BUTTON_LB))
	{
		m_Pos.y--;
	}
}

void DebugCamera::Update()
{
	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;
	m_Pos.z += m_Move.z;

	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	SetCameraPositionAndAngle(m_Pos, m_Rot.x, m_Rot.y, 0.0f);
}

void DebugCamera::Draw()
{

}

void DebugCamera::Fin()
{

}

void DebugCamera::HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult)
{

}