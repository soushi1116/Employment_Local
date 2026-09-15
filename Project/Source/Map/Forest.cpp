#include"DxLib.h"
#include "Forest.h"

Forest::Forest() : MapBase()
{

}

Forest::~Forest()
{
	Fin();
}

void Forest::Init()
{
	m_Type = MAP_FACTORY;
}

void Forest::Load()
{
	m_Handle = MV1LoadModel("Data/Map/Forest/Forest.x");

	m_CollisionHandle = MV1LoadModel("Data/Map/Forest/ForestCollision.x");

	MV1SetScale(m_Handle, VGet(3.0f, 3.0f, 3.0f));

	MV1SetScale(m_CollisionHandle, VGet(0.65f, 1.0f, 0.65f));
}