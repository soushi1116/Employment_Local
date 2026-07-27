#pragma once
#include "DxLib.h"
#include "CharacterParameter.h"

class CollisionAABB;
struct HitResultAABB;
class CollisionSphere;
class Floor;
class BulletBase;
class CharacterBase;

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
	ANIMATION_NONE,
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
	// 基本の処理
	virtual void Init();
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step();
	virtual void Update();
	virtual void DrawModel();
	virtual void DrawUI();
	virtual void Fin();

	virtual void PlayerMove();
	virtual void CPUMove();

	virtual void Respawn(VECTOR pos);

	// コリジョン
	virtual void HitStage(Floor* floor);
	virtual void HitBullet(BulletBase* bullet);
	virtual void HitCharacter(CharacterBase* character);
	bool CheckHitCoin();
	//MV1_COLL_RESULT_POLY_DIM GetHitResult() const { return m_CollisionResult; }
	MV1_COLL_RESULT_POLY_DIM CheckCollisionSphere(VECTOR pos, float r);

	// パラメーター設定
	virtual void SetPosAndIndex(int index, int parentNum);
	virtual void SetColor();
	virtual void SetBoss() { m_IsBoss = true; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void ChangeInBattleScene(bool inBattle) { m_InBattleScene = inBattle; }
	void SetPlayer(bool isPlayer) { m_IsPlayer = isPlayer; }
	void AttackHitFlagTrue() { if (!m_AttackHitFlag) m_AttackHitFlag = true; }
	void AttackHitFlagFalse() { if (m_AttackHitFlag) m_AttackHitFlag = false; }

	// バトル中のアクション
	virtual void Attack();
	virtual void Skill();
	virtual void SuperAttack();
	virtual void Damage(CharacterBase* opponent, int damage);
	void AddSkillPoint() { m_SkillPoint++; }
	void AddKilledNum() { m_KilledNum++; }
	
	// ゲッター
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetMove() { return m_Move; }
	float GetRadius() { return m_Radius; }
	CollisionAABB* GetAABB() { return m_AABB; }
	CollisionSphere* GetSphere() { return m_Sphere; }
	int GetHandle() { return m_Handle; }
	int GetPower() { return m_Power; }
	int GetHP() { return m_Hp; }
	int GetKilledNum() { return m_KilledNum; }
	int GetSkillPoint() { return m_SkillPoint; }
	int GetSuperAttackPoint() { return m_SuperAttackPoint; }
	CharacterType GetType() const { return m_Type; }
	bool GetAttackHitFlag() { return m_AttackHitFlag; }
	bool IsBoss() { return m_IsBoss; }
	bool IsPlayer() { return m_IsPlayer; }
	bool IsDead() { return m_Dead; }
	ActionType GetActionType() { return m_ActionType; }
	CharacterAnimationType GetNowAnimType() { return m_NowAnimation; }

protected:
	// アニメーション
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
	bool m_IsBoss;
	bool m_IsPlayer;
	bool m_InBattleScene;
	bool m_Invisible;

	int m_Handle;
	int m_Power;
	int m_Hp;
	int m_MaxHp;
	int m_RespawnTimer;
	int m_Index;
	int m_SkillPoint;
	int m_SuperAttackPoint;
	int m_KilledNum;
	int m_SkillPointSpend;
	int m_SuperAttackPointSpend;

	float m_Speed;
	float m_Radius;
	float m_Gravity;

	CharacterType m_Type;
	CharacterBase* m_Target;

	CollisionAABB* m_AABB;
	CollisionSphere* m_Sphere;

	ActionType m_ActionType;

	// アニメーション
	int m_AnimationAttachIndex;
	int m_PrevAnimationAttachIndex;
	float m_BlendTime;
	float m_AnimationTotalTime;
	float m_AnimationNowTime;
	bool m_IsLoopAnimation;
	CharacterAnimationType m_NowAnimation;

	float m_AnimTotalTimes[ANIMATION_MAX];
};