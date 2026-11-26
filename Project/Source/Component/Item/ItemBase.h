#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Physics3D;

class ItemBase : public Component
{
public:
	ItemBase(GameObject* owner);
	~ItemBase();

public:
	void Start() override;
	void Update() override;

public:
	void SetType(ItemType type) { m_Type = type; }

	ItemType GetType() const { return m_Type; }

public:

private:
	ItemType m_Type;
	std::weak_ptr<Physics3D> m_Physics;
};
