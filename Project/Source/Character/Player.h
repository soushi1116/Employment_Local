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
};

enum PlayerActionType
{
	PLAYER_ACTION_NONE,
	PLAYER_ACTION_ATTACK,
	PLAYER_ACTION_SKILL,
	PLAYER_ACTION_SUPER_ATTACK,
	PLAYER_ACTION_MAX
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
	CollisionAABB* GetSwordAABB() { return m_SwordAABB; }
	PlayerActionType GetActionType() { return m_ActionType; }
	

private:
	void PlayAnimation(PlayerAnimationType anim, bool isLoop);
	void UpdateAnimation();

private:
	int m_AnimationAttachIndex;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	PlayerActionType m_ActionType;
	PlayerAnimationType m_NowAnimation;

	CollisionAABB* m_SwordAABB;
};

