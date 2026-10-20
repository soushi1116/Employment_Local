#pragma once
#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"
#include <vector>

class DamageCollision : public CollisionBase
{
public:
	DamageCollision(GameObject* owner);
	~DamageCollision();

	void Draw() override;

	float GetRadius() const { return m_Radius; }
	bool IsActive() const { return m_Active; }
	int GetDamage() const { return m_Damage; }
	int GetParentIndex() const { return m_ParentIndex; }
	bool AlreadyHit(int index)
	{
		for (int i : m_HitIndex)
		{
			if (i == index) return true;
		}
		return false;
	}

	void SetRadius(float radius) { m_Radius = radius; }
	void SetActive(bool active) 
	{
		// 非アクティブ→アクティブにするときにHitIndex初期化
		if (active && !m_Active) m_HitIndex.clear();
		m_Active = active;
	}

	void SetDamage(int damage) { m_Damage = damage; }
	void SetParentIndex(int index) { m_ParentIndex = index; }
	void AddHitIndex(int index) { m_HitIndex.push_back(index); }
	void ClearHitIndex() { m_HitIndex.clear(); }

private:
	float m_Radius;
	bool m_Active;
	int m_Damage;
	int m_ParentIndex;
	std::vector<int> m_HitIndex;
};