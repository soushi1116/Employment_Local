#include "DxLib.h"
#include "SphereCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../../MyColor/MyColor.h"
#include "../../GameObject.h"
#include <algorithm>

SphereCollision::SphereCollision(GameObject* owner) : CollisionBase(owner)
{
	m_Radius = 0.0f;
}

SphereCollision::~SphereCollision()
{

}

void SphereCollision::Draw()
{
	m_Radius = (std::max)({ m_Size.x, m_Size.y, m_Size.z }) / 2.0f;

#ifdef _DEBUG
	DrawSphere3D(m_Pos, m_Radius, 16, COLOR_WHITE, COLOR_WHITE, false);
#endif

	
}