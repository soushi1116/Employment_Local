#pragma once
#include <string>
#include "DxLib.h"
#include "../Component.h"

class GameObject;

enum class CharacterType
{
	// Player
	KNIGHT,
	NINJA,
	FAIRY,
	// BOSS
	ROBOT,
	BEAST,
	CHARACTER_TYPE_MAX,
	CHARACTER_TYPE_NONE = -1
};

enum class CharacterAnimationType
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

enum class CharacterAction
{
	ACTION_NONE,
	ACTION_ATTACK,
	ACTION_SKILL,
	ACTION_MAX,
};


class CharacterParameter : public Component
{
public:
	CharacterParameter(GameObject* owner) : Component(owner) {}

	void SetActive(bool active) { m_Active = active; }
	void SetRanding(bool randing) { m_Randing = randing; }
	void SetAttackHitFlag(bool flg) { m_AttackHitFlag = flg; }
	void SetDead(bool dead) { m_Dead = dead; }
	void SetBoss(bool isBoss) { m_IsBoss = isBoss; }
	void SetPlayer(bool isPlayer) { m_IsPlayer = isPlayer; }
	void SetInBattleScene(bool inBattleScene) { m_InBattleScene = inBattleScene; }

	void SetRespawnTimer(int timer) { m_RespawnTimer = timer; }
	void SetIndex(int index) { m_Index = index; }
	void SetKilledNum(int num) { m_KilledNum = num; }

	void SetName(std::string name) { m_Name = name; }
	void SetType(CharacterType type) { m_Type = type; }
	void SetAnim(CharacterAnimationType animType) { m_AnimType = animType; }
	void RenewAnim() { m_PrevAnimType = m_AnimType; }

	void SetAction(CharacterAction action) { m_Action = action; }

	bool IsActive() { return m_Active; }
	bool IsRanding() { return m_Randing; }
	bool GetAttackHitFlag() { return m_AttackHitFlag; }
	bool IsDead() { return m_Dead; }
	bool IsBoss() { return m_IsBoss; }
	bool IsPlayer() { return m_IsPlayer; }
	bool IsInBattleScene() { return m_InBattleScene; }

	bool IsChangeAnim() const{ return (m_PrevAnimType != m_AnimType); }

	int GetIndex() { return m_Index; }
	int GetKilledNum() { return m_KilledNum; }

	std::string GetName() { return m_Name; }

	CharacterType GetType() { return m_Type; }

	CharacterAnimationType GetAnimType() { return m_AnimType; }

	CharacterAction GetAction() { return m_Action; }

private:
	bool m_Active = false;
	bool m_Randing = false;
	bool m_AttackHitFlag = false;
	bool m_Dead = false;
	bool m_IsBoss = false;
	bool m_IsPlayer = false;
	bool m_InBattleScene = false;

	int m_RespawnTimer = 0;
	int m_Index = 0;
	int m_KilledNum = 0;

	std::string m_Name = {};

	CharacterType m_Type = CharacterType::CHARACTER_TYPE_NONE;

	CharacterAction m_Action = CharacterAction::ACTION_NONE;

	CharacterAnimationType m_AnimType = CharacterAnimationType::ANIMATION_NONE;
	CharacterAnimationType m_PrevAnimType = CharacterAnimationType::ANIMATION_NONE;
};

