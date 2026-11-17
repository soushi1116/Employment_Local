#pragma once
#include "ItemBase.h"

class Coin : public ItemBase
{
public:
	Coin(GameObject* owner);
	~Coin();

public:
	void SetRewardPoint(int point) { m_RewardPoint = point; }

	int GetRewardPoint() const { return m_RewardPoint; }

private:
	int m_RewardPoint;
};

