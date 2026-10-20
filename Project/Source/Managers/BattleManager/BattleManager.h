#pragma once
#include <memory>

class GameObject;
class TextRenderer;

enum Member
{
	PLAYER,
	OPPONENT_1,
	OPPONENT_2,
	OPPONENT_3
};

class BattleManager
{
public:
	BattleManager();
	~BattleManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new BattleManager;
		}
	}

	static BattleManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

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

	int GetMinute() { return m_TimerMinute; }
	int GetSuperAttackNum() { return m_SuperAttackNum; }
	int GetKilledNum() { return m_killedNum; }
	int GetNoDamageTimer() { return m_NoDamageTimerSecond; }
	int GetNoMoveTimer() { return m_NoMoveTimerSecond; }
	bool IsBossWin() { return m_BossWin; }
	bool IsChallengerWin() { return m_ChallengerWin; }
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

private:
	static BattleManager* m_Instance;

	bool m_BossWin;
	bool m_ChallengerWin;

	int m_EndTime;
	float m_Timer;
	int m_TimerSecond;
	int m_TimerMinute;
	float m_TimerFrame;

	int m_NoDamageTimerFrame;
	int m_NoDamageTimerSecond;
	int m_NoMoveTimerFrame;
	int m_NoMoveTimerSecond;

	int m_SuperAttackNum;

	int m_killedNum;

	int m_TimerFrameHandle;

	Member m_BossMember;

	std::shared_ptr<GameObject> m_TimerObj;
	std::shared_ptr<TextRenderer> m_TimerText;
};

