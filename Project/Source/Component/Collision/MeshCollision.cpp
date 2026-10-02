#include "DxLib.h"
#include "MeshCollision.h"
#include "../../MyMath/MyMath.h"
#include "../../MyColor/MyColor.h"
#include "../GameObject.h"

MeshCollision::MeshCollision(GameObject* owner) : CollisionBase(owner)
{
	m_Pos = MyMath::VecZero();
	m_CollisionHandle = 0;
}

MeshCollision::~MeshCollision()
{

}

void MeshCollision::Draw()
{
	m_Pos = m_Owner->GetComponent<Transform>()->GetPos();

	MV1SetPosition(m_CollisionHandle, m_Pos);

	MV1DrawModel(m_CollisionHandle);
}

void MeshCollision::SetCollisionHandle(const char* filePath)
{
	m_CollisionHandle = MV1LoadModel(filePath);
}