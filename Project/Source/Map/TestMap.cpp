#include"DxLib.h"
#include "TestMap.h"

TestMap::TestMap() : MapBase()
{

}

TestMap::~TestMap()
{
	Fin();
}

void TestMap::Init()
{
	m_Type = MAP_FACTORY;
}

void TestMap::Load()
{
	m_Handle = MV1LoadModel("Data/Map/Test/TestStage.x");

	m_CollisionHandle = MV1LoadModel("Data/Map/Test/TestStageCollision.x");
}