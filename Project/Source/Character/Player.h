#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

enum PlayerAnimationType
{
	PLAYER_ANIMATION_STOP,
	PLAYER_ANIMATION_WALK,
	PLAYER_ANIMATION_ATTACK,
};

class Player : public CharacterBase
{
public:
	Player();
	~Player();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

private:
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();

private:
	int m_AnimationAttachIndex;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	bool m_Attacking;
	PlayerAnimationType m_NowAnimation;
};

