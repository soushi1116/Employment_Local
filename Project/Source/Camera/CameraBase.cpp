#include "CameraBase.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"

CameraBase::CameraBase()
{
	m_Pos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Target = MyMath::VecZero();
	m_UpVec = MyMath::VecZero();

	m_TargetCharacter = nullptr;
}

CameraBase::~CameraBase()
{
	
}