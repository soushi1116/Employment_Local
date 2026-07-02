#pragma once
#include "DxLib.h"
#include "CharacterParameter.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;
class Floor;

enum ActionType
{
	ACTION_TYPE_NONE,
	ACTION_ATTACK,
	ACTION_SKILL,
	ACTION_SUPER_ATTACK,
	ACTION_DAMAGED,
	ACTION_DIE,
	ACTION_TYPE_MAX
};

enum CharacterAnimationType
{
	ANIMATION_STOP,
	ANIMATION_WALK,
	ANIMATION_ATTACK,
	ANIMATION_SKILL,
	ANIMATION_SUPER_ATTACK,
	ANIMATION_DIE,
	ANIMATION_DAMAGED,
	ANIMATION_MAX
};

class CharacterBase
{
public:
	CharacterBase();
	virtual ~CharacterBase();

public:
	virtual void Init();
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step() = 0;

	virtual void Update();
	virtual void DrawModel();
	virtual void DrawUI();
	virtual void Fin();

	virtual void Respawn(VECTOR pos);

	virtual void HitFloor(Floor* floor);

	virtual void Damage(CharacterBase* opponent);

	virtual void SetPosAndIndex(int index, int parentNum);

	virtual void SetColor();

	virtual void SetParent() { m_IsParent = true; }

	virtual void Attack();
	virtual void Skill();
	virtual void SuperAttack();

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void ChangeInBattleScene(bool inBattle) { m_InBattleScene = inBattle; }

	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetMove() { return m_Move; }

	float GetRadius() { return 5.0f; }

	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	int GetHandle() { return m_Handle; }
	int GetPower() { return m_Power; }
	int GetHP() { return m_Hp; }
	int GetKilledNum() { return m_KilledNum; }
	int GetSkillPoint() { return m_SkillPoint; }
	int GetSuperAttackPoint() { return m_SuperAttackPoint; }

	CharacterType GetType() const { return m_Type; }

	void AttackHitFlagTrue() { if (!m_AttackHitFlag) m_AttackHitFlag = true; }
	void AttackHitFlagFalse() { if (m_AttackHitFlag) m_AttackHitFlag = false; }

	bool GetAttackHitFlag() { return m_AttackHitFlag; }
	bool IsParent() { return m_IsParent; }
	
	ActionType GetActionType() { return m_ActionType; }

	void AddSkillPoint() { m_SkillPoint++; }

	void AddKilledNum() { m_KilledNum++; }

	bool CheckHitCoin();

protected:
	virtual void PlayAnimation(CharacterAnimationType anim, bool isLoop);
	virtual void UpdateAnimation();

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;
	VECTOR m_DefaultPos;

	bool m_Active;
	bool m_Randing;
	bool m_AttackHitFlag;
	bool m_Dead;
	bool m_IsParent;
	bool m_InBattleScene;

	int m_Handle;
	int m_Power;
	int m_Hp;
	int m_MaxHp;
	int m_RespawnTimer;
	int m_Index;
	int m_SkillPoint;
	int m_SuperAttackPoint;
	int m_KilledNum;

	float m_Speed;

	float m_Gravity;

	CharacterType m_Type;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;

	ActionType m_ActionType;

	int m_AnimationAttachIndex;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	CharacterAnimationType m_NowAnimation;

	float m_AnimTotalTimes[ANIMATION_MAX];
};