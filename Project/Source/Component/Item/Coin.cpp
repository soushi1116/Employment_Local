#include "Coin.h"
#include "../GameObject.h"

Coin::Coin(GameObject* owner) :
	ItemBase(owner)
	, m_RewardPoint(0)
{

}

Coin::~Coin()
{

}
