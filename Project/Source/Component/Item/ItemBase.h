#pragma once
#include "../Component.h"
#include <memory>

class GameObject;

class ItemBase : public Component
{
public:
	ItemBase(GameObject* owner);
	~ItemBase();

public:
	void SetType(ItemType type) { m_Type = type; }

	ItemType GetType() const { return m_Type; }

public:

private:
	ItemType m_Type;

};
