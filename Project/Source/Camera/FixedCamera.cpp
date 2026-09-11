#include "FixedCamera.h"
#include "../MyMath/MyMath.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"

const float CAMERA_NEAR_CLIP = 0.01f;
const float CAMERA_FAR_CLIP = 1000.0f;

VECTOR CHARACTER_SELECT_SCENE_POS = VGet(0.0f, 10.0f, 50.0f);
VECTOR CHARACTER_SELECT_SCENE_TARGET = VGet(20.0f, 10.0f, 0.0f);
VECTOR CHARACTER_SELECT_SCENE_UP_VEC = VGet(0.0f, 1.0f, 0.0f);

FixedCamera::FixedCamera()
{

}

FixedCamera::~FixedCamera()
{
    Fin();
}

void FixedCamera::Init()
{

}

void FixedCamera::Load()
{

}

void FixedCamera::Start()
{
    m_Pos = CHARACTER_SELECT_SCENE_POS;
    m_Target = CHARACTER_SELECT_SCENE_TARGET;
    m_UpVec = CHARACTER_SELECT_SCENE_UP_VEC;

    SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);
}

void FixedCamera::Step()
{

}

void FixedCamera::Update()
{
    
}

void FixedCamera::Draw()
{
    SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
    DrawFormatString(0, 60, GetColor(255, 255, 255), "カメラの座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
    DrawFormatString(0, 840, GetColor(255, 255, 255), "カメラの注視点[%f, %f, %f]", m_Target.x, m_Target.y, m_Target.z);
}

void FixedCamera::Fin()
{

}

void FixedCamera::HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult)
{

}