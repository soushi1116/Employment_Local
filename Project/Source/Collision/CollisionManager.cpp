#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "../Character/CharacterManager.h"
#include "../Floor/FloorManager.h"

CollisionManager* CollisionManager::m_Instance = nullptr;

CollisionManager::CollisionManager()
{
	m_AABB = {};
}

CollisionManager::~CollisionManager()
{
	Fin();
}

void CollisionManager::Draw()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		delete aabb;
	}

	m_AABB.clear();
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* aabb = new CollisionAABB;
	m_AABB.push_back(aabb);

	return aabb;
}
