#include "ResultCamera.h"
#include "../MyMath/MyMath.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"

const float CAMERA_NEAR_CLIP = 0.01f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float PLAYER_DISTANCE = -100.0f;
const float ROTATION_SPEED = 0.03f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;

ResultCamera::ResultCamera()
{
	
}

ResultCamera::~ResultCamera()
{
	Fin();
}

void ResultCamera::Init()
{

}

void ResultCamera::Load()
{

}

void ResultCamera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);
}

void ResultCamera::Step()
{

}

void ResultCamera::Update()
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
	m_Target.y += 8.0f;
	m_Target.z += 100.0f;

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void ResultCamera::Draw()
{
	//DrawFormatString(0, 60, GetColor(255, 255, 255), "ÉJÉÅÉâÇÃç¿ïW[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void ResultCamera::Fin()
{

}