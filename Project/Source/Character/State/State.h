#pragma once
#include "../CharacterParameter.h"
#include "../../MyMath/MyMath.h"

class State
{
public:
	State();
	~State();

public:
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw(int index);
	void Fin();

	void SetType(StateType type) { m_Type = type; }
	void SetMaxTime(int time) { m_MaxTime = time; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void FulFillTime() { m_Timer = m_MaxTime; }
	void SetActive(bool active) { m_Active = active; }

	StateType GetType() const{ return m_Type; }
	bool IsActive() const{ return m_Active; }

private:
	StateType m_Type;
	int m_IconHandle;
	int m_Timer;
	int m_MaxTime;
	bool m_Active;
	VECTOR m_Pos;
};

