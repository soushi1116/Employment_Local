#include "DxLib.h"
#include "MeshCollision.h"
#include "../../../MyMath/MyMath.h"
#include "../../../MyColor/MyColor.h"
#include "../../GameObject.h"

MeshCollision::MeshCollision()
{
	m_CollisionHandle = 0;
}

MeshCollision::~MeshCollision()
{

}

void MeshCollision::Draw()
{
	MV1SetPosition(m_CollisionHandle, m_Pos);

	MV1RefreshCollInfo(m_CollisionHandle, -1);

	//MV1DrawModel(m_CollisionHandle);
}

void MeshCollision::SetCollisionHandle(const char* filePath)
{
	m_CollisionHandle = MV1LoadModel(filePath);

	MV1SetupCollInfo(m_CollisionHandle, -1, 8, 8, 8);
}