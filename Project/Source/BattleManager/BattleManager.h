#pragma once

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
	int GetMinute() { return m_TimerMinute; }
	int GetSuperAttackNum() { return m_SuperAttackNum; }
	int GetKilledNum() { return m_killedNum; }
	int GetNoDamageTimer() { return m_NoDamageTimerSecond; }
	int GetNoMoveTimer() { return m_NoMoveTimerSecond; }
	bool IsParentWin() { return m_PatentWin; }
	bool IsChildWin() { return m_ChildWin; }
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
	void ParentWin() { m_PatentWin = true; }
	void ChildWin() { m_ChildWin = true; }

private:
	static BattleManager* m_Instance;

	bool m_PatentWin;
	bool m_ChildWin;

	int m_TimerFrame;
	int m_TimerSecond;
	int m_TimerMinute;

	int m_NoDamageTimerFrame;
	int m_NoDamageTimerSecond;
	int m_NoMoveTimerFrame;
	int m_NoMoveTimerSecond;

	int m_SuperAttackNum;

	int m_killedNum;
};

