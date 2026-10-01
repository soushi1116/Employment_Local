#pragma once
#include <string>
#include "DxLib.h"
#include "../Component.h"

class GameObject;

class CharacterParameter : public Component
{
	enum CharacterType
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

	bool IsActive() { return m_Active; }
	bool IsRanding() { return m_Randing; }
	bool GetAttackHitFlag() { return m_AttackHitFlag; }
	bool IsDead() { return m_Dead; }
	bool IsBoss() { return m_IsBoss; }
	bool IsPlayer() { return m_IsPlayer; }
	bool IsInBattleScene() { return m_InBattleScene; }

	int GetIndex() { return m_Index; }
	int GetKilledNum() { return m_KilledNum; }

	std::string GetName() { return m_Name; }

	CharacterType GetType() { return m_Type; }

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

	CharacterType m_Type = CHARACTER_TYPE_NONE;

};

