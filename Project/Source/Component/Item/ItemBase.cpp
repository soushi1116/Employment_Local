#include "ItemBase.h"
#include "../GameObject.h"
#include "../Component.h"

ItemBase::ItemBase(GameObject* owner)
	: Component(owner)
	, m_Type(ITEM_TYPE_NONE)
{

}

ItemBase::~ItemBase()
{

}