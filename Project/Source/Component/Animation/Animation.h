#pragma once
#include <memory>
#include <vector>
#include "../Component.h"
#include "../Character/CharacterParameter.h"

class GameObject;
class ModelRenderer;

class Animation
{
public:
	struct AnimData
	{
		int m_Index;
		float m_TotalTime;
		float m_AnimSpeed;
		bool m_IsLoopAnimation;
		CharacterAnimationType m_AnimType;
		CharacterType m_CharacterType;
	};

	Animation();
	~Animation();

	void SetAnimData(CharacterType characterType, CharacterAnimationType animType);

	AnimData GetAnimData() const { return m_AnimData; }

	CharacterAnimationType GetType() const { return m_AnimData.m_AnimType; }

private:
	AnimData m_AnimData;
};