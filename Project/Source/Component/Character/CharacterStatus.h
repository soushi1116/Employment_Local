#pragma once
#include "../Component.h"
//#include <list>

class GameObject;

class CharacterStatus : public Component
{
public:
	CharacterStatus(GameObject* owner) : Component(owner) {}

	void SetPower(int power) { m_Power = power; }
	void SetHp(int hp) { m_Hp = hp; }
	void SetMaxHp(int hp) { m_MaxHp = hp; }
	void SetSkillPointSpend(int point) { m_SkillPointSpend = point; }
	void SetSuperAttackPointSpend(int point) { m_SuperAttackPointSpend = point; }

	void AddSkillPoint(int point) { m_SkillPoint += point; }
	void AddSuperAttackPoint(int point) { m_SuperAttackPoint += point; }
	
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

	void AddPowermagni(float magni) { m_PowerMagni *= magni; }
	void AddDefencemagni(float magni) { m_DefenceMagni *= magni; }

	int GetPower() { return m_Power; }
	int GetHp() { return m_Hp; }
	int GetMaxHp() { return m_MaxHp; }
	int GetSkillPoint() { return m_SkillPoint; }
	int GetSuperAttackPoint() { return m_SuperAttackPoint; }

	float GetSpeed() { return m_Speed; }
	float GetAttackRange() { return m_AttackRange; }
	float GetSuperAttackRange() { return m_SuperAttackRange; }
	float GetPowerMagni() { return m_PowerMagni; }
	float GetDefenceMagni() { return m_DefenceMagni; }

private:
	int m_Power = 0;
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

	//std::list<State*> m_StateList;
};