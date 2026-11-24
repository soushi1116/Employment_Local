#include "Animation.h"
#include "../GameObject.h"
#include "../../Managers/AnimationManager/AnimationManager.h"

Animation::Animation()
	:m_AnimData{
		0,
		0.0f,
		0.0f,
		false,
		ANIMATION_NONE,
		CHARACTER_TYPE_NONE
	}
{

}

Animation::~Animation()
{

}

/// <summary>
/// アニメーションのデータを設定
/// </summary>
/// <param name="characterType">キャラクターの種類</param>
/// <param name="animType">アニメーションの種類</param>
void Animation::SetAnimData(CharacterType characterType, CharacterAnimationType animType)
{
	m_AnimData.m_Index = static_cast<int>(animType);
	m_AnimData.m_CharacterType = characterType;
	m_AnimData.m_TotalTime = AnimationManager::GetInstance()->GetTotalTime(characterType, animType);
	m_AnimData.m_AnimType = animType;

	switch (animType)
	{
	case CharacterAnimationType::ANIMATION_NONE:
		break;
	case CharacterAnimationType::ANIMATION_STOP:
		m_AnimData.m_IsLoopAnimation = true;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_WALK:
		m_AnimData.m_IsLoopAnimation = true;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_ATTACK:
		m_AnimData.m_IsLoopAnimation = false;
		if (characterType == KNIGHT) m_AnimData.m_AnimSpeed = 0.5f;
		else m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_SKILL:
		m_AnimData.m_IsLoopAnimation = false;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_SUPER_ATTACK:
		m_AnimData.m_IsLoopAnimation = false;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_DIE:
		m_AnimData.m_IsLoopAnimation = false;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_DAMAGED:
		m_AnimData.m_IsLoopAnimation = false;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_RUN:
		m_AnimData.m_IsLoopAnimation = true;
		m_AnimData.m_AnimSpeed = 0.3f;
		break;
	case CharacterAnimationType::ANIMATION_MAX:
		break;
	default:
		break;
	}
}