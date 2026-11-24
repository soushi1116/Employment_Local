#pragma once
#include <memory>
#include "../MapManager/MapManager.h"
#include "../Singleton.h"

class GameObject;
class TextRenderer;
class Timer;

enum Member
{
	PLAYER,
	OPPONENT_1,
	OPPONENT_2,
	OPPONENT_3,

	MEMBER_NONE = -1
};

class BattleManager : public Singleton<BattleManager>
{
public:
	BattleManager();
	~BattleManager();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void BattleStart();

	int GetSuperAttackNum() const { return m_SuperAttackNum; }
	int GetKilledNum() const { return m_killedNum; }
	int GetDamageAmount() const { return m_DamageAmount; }
	int GetNoDamageTimer() const { return m_NoDamageTimerSecond; }
	int GetNoMoveTimer() const { return m_NoMoveTimerSecond; }
	bool IsBossWin() const { return m_BossWin; }
	bool IsChallengerWin() const { return m_ChallengerWin; }
	void AddSuperAttackNum() { m_SuperAttackNum++; }
	void ResetNoDamageTimer()
	{
		m_NoDamageTimerFrame = 0;
		m_NoDamageTimerSecond = 0;
	}
	void ResetNoMoveTimer()
	{
		m_NoMoveTimerFrame = 0;
		m_NoMoveTimerSecond = 0;
	}
	void BossWin() { m_BossWin = true; }
	void ChallengerWin() { m_ChallengerWin = true; }
	void SetBossMember(Member member) { m_BossMember = member; }
	Member GetBossMember() const { return m_BossMember; }

	void SetMapType(MapType type) { m_CurrentMapType = type; }
	MapType GetMapType() const { return m_CurrentMapType; }

	void AddKilledNum() { m_killedNum++; }
	void AddDamageAmount(int damage) { m_DamageAmount += damage; }

private:
	static BattleManager* m_Instance;

	bool m_BossWin;
	bool m_ChallengerWin;

	int m_NoDamageTimerFrame;
	int m_NoDamageTimerSecond;
	int m_NoMoveTimerFrame;
	int m_NoMoveTimerSecond;

	int m_SuperAttackNum;

	int m_killedNum;
	int m_DamageAmount;

	int m_TimerFrameHandle;

	Member m_BossMember;

	std::weak_ptr<GameObject> m_TimerObj;
	std::weak_ptr<TextRenderer> m_TimerText;
	std::weak_ptr<Timer> m_TimerCmp;

	MapType m_CurrentMapType;
};

