#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class CollisionAABB;
struct HitResultAABB;

enum EnemyAnimationType
{
	ENEMY_ANIMATION_STOP,
	ENEMY_ANIMATION_WALK,
	ENEMY_ANIMATION_ATTACK,
	ENEMY_ANIMATION_SKILL,
	ENEMY_ANIMATION_SUPER_ATTACK,
	ENEMY_ANIMATION_DIE,
	ENEMY_ANIMATION_DAMAGED,
	ENEMY_ANIMATION_MAX
};

class Enemy : public CharacterBase
{
public:
	Enemy();
	~Enemy();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	void Damage(CharacterBase* opponent) override;

private:
	void PlayAnimation(EnemyAnimationType anim, bool isLoop);
	void UpdateAnimation();

private:
	int m_AnimationAttachIndex;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	EnemyAnimationType m_NowAnimation;

	float m_AnimTotalTimes[ENEMY_ANIMATION_MAX];

	int m_MoveDir;
	
};

