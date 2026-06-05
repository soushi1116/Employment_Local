#include "Camera.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"

const float CAMERA_NEAR_CLIP = 0.01f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float PLAYER_DISTANCE = -7.0f;
const float ROTATION_SPEED = 0.01f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;

Camera::Camera()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	m_UpVec = VGet(0.0f, 0.0f, 0.0f);

	m_TargetCharacter = nullptr;
}

Camera::~Camera()
{
	Fin();
}

void Camera::Init()
{

}

void Camera::Load()
{

}

void Camera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	m_TargetCharacter = CharacterManager::GetInstance()->GetCharacter(PLAYER);
}

void Camera::Step()
{

}

void Camera::Update()
{

}

void Camera::Draw()
{

}

void Camera::Fin()
{

}