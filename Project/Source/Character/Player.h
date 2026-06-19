#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

enum PlayerAnimationType
{
	PLAYER_ANIMATION_STOP,
	PLAYER_ANIMATION_WALK,
	PLAYER_ANIMATION_ATTACK,
	PLAYER_ANIMATION_SKILL,
	PLAYER_ANIMATION_SUPER_ATTACK,
	PLAYER_ANIMATION_DIE,
	PLAYER_ANIMATION_DAMAGED,
	PLAYER_ANIMATION_MAX
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

public:
	

private:
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();

private:
	int m_AnimationAttachIndex;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	PlayerAnimationType m_NowAnimation;

	float m_AnimTotalTimes[PLAYER_ANIMATION_MAX];
};

