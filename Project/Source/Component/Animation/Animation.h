#pragma once
#include <memory>
#include <vector>
#include "../Component.h"

class GameObject;
class ModelRenderer;

enum CharacterAnimationType
{
	ANIMATION_NONE,
	ANIMATION_STOP,
	ANIMATION_WALK,
	ANIMATION_ATTACK,
	ANIMATION_SKILL,
	ANIMATION_SUPER_ATTACK,
	ANIMATION_DIE,
	ANIMATION_DAMAGED,
	ANIMATION_RUN,
	ANIMATION_MAX
};


class Animation
{
public:
	struct AnimData
	{
		int m_Index;
		float m_TotalTime;
		bool m_IsLoopAnimation;
		CharacterAnimationType m_Type;
	};

	Animation();
	~Animation();

	void SetAnimData(CharacterAnimationType type);

	AnimData GetAnimData() const { return m_AnimData; }

	CharacterAnimationType GetType() { return m_AnimData.m_Type; }

private:
	AnimData m_AnimData;
};