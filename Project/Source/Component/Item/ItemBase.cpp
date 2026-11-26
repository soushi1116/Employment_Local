#include "ItemBase.h"
#include "../GameObject.h"
#include "../Component.h"

constexpr float ITEM_ROT_SPEED = DX_PI_F / 120.0f;

ItemBase::ItemBase(GameObject* owner)
	: Component(owner)
	, m_Type(ITEM_TYPE_NONE)
{

}

ItemBase::~ItemBase()
{

}

void ItemBase::Start()
{
	m_Physics = m_Owner->GetComponent<Physics3D>();
}

void ItemBase::Update()
{
	if (auto physicsShared = m_Physics.lock())
	{
		float newAngleY = physicsShared->GetDirAngleY() + ITEM_ROT_SPEED;
		physicsShared->SetDirAngleY(newAngleY);
	}
}