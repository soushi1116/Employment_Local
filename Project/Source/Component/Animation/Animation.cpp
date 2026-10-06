#include "Animation.h"
#include "../GameObject.h"

Animation::Animation()
{
	m_AnimData.m_Index = 0;
	m_AnimData.m_TotalTime = 0.0f;
	m_AnimData.m_IsLoopAnimation = false;
	m_AnimData.m_Type = ANIMATION_NONE;
}

Animation::~Animation()
{

}


void Animation::SetAnimData(CharacterAnimationType type)
{
	m_AnimData.m_Index = static_cast<int>(type);

	switch (type)
	{
	case ANIMATION_NONE:
		break;
	case ANIMATION_STOP:
		m_AnimData.m_IsLoopAnimation = true;
		break;
	case ANIMATION_WALK:
		m_AnimData.m_IsLoopAnimation = true;
		break;
	case ANIMATION_ATTACK:
		m_AnimData.m_IsLoopAnimation = false;
		break;
	case ANIMATION_SKILL:
		m_AnimData.m_IsLoopAnimation = false;
		break;
	case ANIMATION_SUPER_ATTACK:
		m_AnimData.m_IsLoopAnimation = false;
		break;
	case ANIMATION_DIE:
		m_AnimData.m_IsLoopAnimation = false;
		break;
	case ANIMATION_DAMAGED:
		m_AnimData.m_IsLoopAnimation = false;
		break;
	case ANIMATION_RUN:
		m_AnimData.m_IsLoopAnimation = true;
		break;
	case ANIMATION_MAX:
		break;
	default:
		break;
	}
}