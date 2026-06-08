#include "CameraBase.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

CameraBase::CameraBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Target = VGet(0.0f, 0.0f, 0.0f);
	m_UpVec = VGet(0.0f, 0.0f, 0.0f);
}

CameraBase::~CameraBase()
{
	
}