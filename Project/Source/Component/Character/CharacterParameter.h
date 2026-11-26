#pragma once
#include <string>
#include <memory>
#include <vector>
#include "DxLib.h"
#include "../Component.h"
#include "../../MyMath/MyMath.h"

constexpr int SKILL_AND_SUPER_ATTACK_POINT_MAX = 1800;
constexpr int SKILL_AND_SUPER_ATTACK_POINT_SPEND = 1000;

class GameObject;
class DamageCollision;
class CharacterState;

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
	void AddKillNum() { m_KillNum ++; }

	void SetName(std::string name) { m_Name = name; }
	void SetType(CharacterType type) { m_Type = type; }
	void SetAnim(CharacterAnimationType animType) { m_AnimType = animType; }
	void RenewAnim() { m_PrevAnimType = m_AnimType; }

	void SetAction(CharacterAction action) { m_Action = action; }

	void SetAttackCollision(std::weak_ptr<DamageCollision> collision) { m_AttackCollision = collision; }
	void SetSuperAttackCollision(std::weak_ptr<DamageCollision> collision) { m_SuperAttackCollision = collision; }

	bool IsActive() const { return m_Active; }
	bool IsRanding() const { return m_Randing; }
	bool GetAttackHitFlag() const { return m_AttackHitFlag; }
	bool IsDead() const { return m_Dead; }
	bool IsBoss() const { return m_IsBoss; }
	bool IsPlayer() const { return m_IsPlayer; }
	bool IsInBattleScene() const { return m_InBattleScene; }

	bool IsChangeAnim() const{ return (m_PrevAnimType != m_AnimType); }

	int GetIndex() const { return m_Index; }
	int GetKilledNum() const { return m_KilledNum; }
	int GetKillNum() const { return m_KillNum; }

	std::string GetName() const { return m_Name; }

	CharacterType GetType() const { return m_Type; }

	CharacterAnimationType GetAnimType() const { return m_AnimType; }

	CharacterAction GetAction() const { return m_Action; }

	std::weak_ptr<DamageCollision> GetAttackCollision() const { return m_AttackCollision; }
	std::weak_ptr<DamageCollision> GetSuperAttackCollision() const { return m_SuperAttackCollision; }

	void SetPower(int power) { m_Power = power; }
	void SetSuperAttackPower(int power) { m_SuperAttackPower = power; }
	void SetHp(int hp) { m_Hp = hp; }
	void SetMaxHp(int hp) { m_MaxHp = hp; }
	void SetSkillPointSpend(int point) { m_SkillPointSpend = point; }
	void SetSuperAttackPointSpend(int point) { m_SuperAttackPointSpend = point; }

	void SetStartPos(VECTOR pos) { m_StartPos = pos; }
	VECTOR GetStartPos() const { return m_StartPos; }

	void AddSkillPoint(int point) 
	{
		m_SkillPoint += point;

		if (m_SkillPoint > SKILL_AND_SUPER_ATTACK_POINT_MAX)
		{
			m_SkillPoint = SKILL_AND_SUPER_ATTACK_POINT_MAX;
		}
	}

	void AddSuperAttackPoint(int point) 
	{ 
		m_SuperAttackPoint += point;

		if (m_SuperAttackPoint > SKILL_AND_SUPER_ATTACK_POINT_MAX)
		{
			m_SuperAttackPoint = SKILL_AND_SUPER_ATTACK_POINT_MAX;
		}
	}

	void IncreaseHP(int amount)
	{
		m_Hp += amount;
		if (m_Hp > m_MaxHp)
		{
			m_Hp = m_MaxHp;
		}
	}

	void DecreaseHP(int amount)
	{
		m_Hp -= amount;
		if (m_Hp < 0)
		{
			m_Hp = 0;
		}
	}

	void SpendSkillPoint()
	{
		m_SkillPoint -= m_SkillPointSpend;

		if (m_SkillPoint < 0)
		{
			m_SkillPoint = 0;
		}
	}

	void SpendSuperAttackPoint()
	{
		m_SuperAttackPoint -= m_SuperAttackPointSpend;

		if (m_SuperAttackPoint < 0)
		{
			m_SuperAttackPoint = 0;
		}
	}

	void SetSpeed(float speed) { m_Speed = speed; }
	void SetAttackRange(float range) { m_AttackRange = range; }
	void SetSuperAttackRange(float range) { m_SuperAttackRange = range; }

	void SetStatus(std::vector<float> statusData)
	{
		m_MaxHp = static_cast<int>(statusData[MAX_HP]);
		m_Power = static_cast<int>(statusData[POWER]);
		m_SuperAttackPower = static_cast<int>(statusData[SUPER_ATTACK_POWER]);
		m_Speed = statusData[SPEED];
		m_AttackRange = statusData[ATTACK_RANGE];
		m_SuperAttackRange = statusData[SUPER_ATTACK_RANGE];
	}

	void AddPowerMagni(float magni) { m_PowerMagni *= magni; }
	void AddDefenceMagni(float magni) { m_DefenceMagni *= magni; }
	void AddSpeedMagni(float magni) { m_SpeedMagni *= magni; }

	int GetPower() const { return m_Power; }
	int GetSuperAttackPower() const { return m_SuperAttackPower; }
	int GetHp() const { return m_Hp; }
	int GetMaxHp() const { return m_MaxHp; }
	int GetSkillPoint() const { return m_SkillPoint; }
	int GetSuperAttackPoint() const { return m_SuperAttackPoint; }

	float GetSpeed() const { return m_Speed; }
	float GetAttackRange() const { return m_AttackRange; }
	float GetSuperAttackRange() const { return m_SuperAttackRange; }
	float GetPowerMagni() const { return m_PowerMagni; }
	float GetDefenceMagni() const { return m_DefenceMagni; }
	float GetSpeedMagni() const { return m_SpeedMagni; }

	bool ActionAble() const // éÄñSÅEçUåÇÅEÉXÉLÉãÅEïKéEãZÇ¢Ç∏ÇÍÇ©ÇÃÉÇÅ[ÉVÉáÉìíÜÇ≈Ç»Ç¢Ç©
	{
		if (m_Action != CharacterAction::ACTION_DIE && 
			m_Action != CharacterAction::ACTION_ATTACK &&
			m_Action != CharacterAction::ACTION_SKILL &&
			m_Action != CharacterAction::ACTION_SUPER_ATTACK)
		{
			return true;
		}
		return false;
	}

	void AddState(std::weak_ptr<GameObject> state) { m_States.push_back(state); }

	std::vector<std::weak_ptr<GameObject>>& GetStates() { return m_States; }

	void SetActionSEPlayed(bool played) { m_ActionSEPlayed = played; }
	bool IsActionSEPlayed() const{ return m_ActionSEPlayed; }

	int GetCurrentPower() const { return static_cast<int>(static_cast<float>(m_Power) * m_PowerMagni); }
	float GetCurrentSpeed() const { return (static_cast<float>(m_Speed) * m_SpeedMagni); }

private:
	bool m_Active = false;
	bool m_Randing = false;
	bool m_AttackHitFlag = false;
	bool m_Dead = false;
	bool m_IsBoss = false;
	bool m_IsPlayer = false;
	bool m_InBattleScene = false;
	bool m_ActionSEPlayed = false;;

	int m_RespawnTimer = 0;
	int m_Index = 0;
	int m_KilledNum = 0;

	int m_KillNum = 0;

	std::string m_Name = {};

	CharacterType m_Type = CharacterType::CHARACTER_TYPE_NONE;

	CharacterAction m_Action = CharacterAction::ACTION_NONE;

	CharacterAnimationType m_AnimType = CharacterAnimationType::ANIMATION_NONE;
	CharacterAnimationType m_PrevAnimType = CharacterAnimationType::ANIMATION_NONE;

	std::weak_ptr<DamageCollision> m_AttackCollision;
	std::weak_ptr<DamageCollision> m_SuperAttackCollision;

	int m_Power = 0;
	int m_SuperAttackPower = 0;
	int m_Hp = 0;
	int m_MaxHp = 0;
	int m_SkillPoint = 0;
	int m_SuperAttackPoint = 0;
	int m_SkillPointSpend = 0;
	int m_SuperAttackPointSpend = 0;

	float m_Speed = 0.0f;
	float m_AttackRange = 0.0f;
	float m_SuperAttackRange = 0.0f;
	float m_PowerMagni = 1.0f;
	float m_DefenceMagni = 1.0f;
	float m_SpeedMagni = 1.0f;

	VECTOR m_StartPos = MyMath::VecZero();

	std::vector<std::weak_ptr<GameObject>> m_States;
};

