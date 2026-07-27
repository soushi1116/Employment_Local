#include "SkyDome.h"
#include "../MyMath/MyMath.h"

SkyDome::SkyDome()
{
	m_Handle = 0;
	m_Pos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
}

SkyDome::~SkyDome()
{
	Fin();
}

void SkyDome::Load()
{
	m_Handle = MV1LoadModel("Data/SkyDome/SkyDome.x");
}

void SkyDome::Step()
{

}

void SkyDome::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);

	m_Scale = VGet(10.0f, 10.0f, 10.0f);

	MV1SetScale(m_Handle, m_Scale);
}

void SkyDome::Draw()
{
	MV1DrawModel(m_Handle);
}

void SkyDome::Fin()
{
	MV1DeleteModel(m_Handle);
}