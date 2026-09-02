#include"DxLib.h"
#include "Factory.h"

Factory::Factory() : MapBase()
{
	
}

Factory::~Factory()
{
	Fin();
}

void Factory::Init()
{
	m_Type = MAP_FACTORY;
}

void Factory::Load()
{
	m_Handle = MV1LoadModel("Data/Map/Factory/Factory.x");

	m_CollisionHandle = MV1LoadModel("Data/Map/Factory/FactoryCollision.x");
}