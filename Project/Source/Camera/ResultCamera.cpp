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

    m_Target = playerPos;
    m_Target.y += m_TargetCharacter->GetRadius() * 1.25f;
    m_Target.x += 20.0f;

    m_Pos.x = playerPos.x += 22.0f;
    m_Pos.y = playerPos.y + (m_TargetCharacter->GetRadius() * 1.5f);
    m_Pos.z = playerPos.z + 50.0f;

    m_UpVec = VGet(0.0f, 1.0f, 0.0f);
}

void ResultCamera::Draw()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
	DrawFormatString(0, 840, GetColor(255, 255, 255), "カメラの注視点[%f, %f, %f]", m_Target.x, m_Target.y, m_Target.z);
}

void ResultCamera::Fin()
{

}

void ResultCamera::HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult)
{

}