#include "GimmickBase.h"
#include "../GameObject.h"
#include "../Component.h"

GimmickBase::GimmickBase(GameObject* owner)
	: Component(owner)
	,m_Type(GIMMICK_TYPE_NONE)
{
	
}

GimmickBase::~GimmickBase()
{

}