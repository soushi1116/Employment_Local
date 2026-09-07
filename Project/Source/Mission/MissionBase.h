#pragma once
#include "DxLib.h"
#include "MissionParameter.h"
#include "../UI/UIManager.h"
#include "../UI/UIText.h"

class MissionBase
{
public:
	MissionBase();
	~MissionBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step() = 0;
	virtual void Update();
	virtual void Draw(int index);
	virtual void Fin();

public:
	MissionType GetType() { return m_Type; }
	void SetType(MissionType type) { m_Type = type; }
	void SetSelected() { m_IsSelected = true; }
	void Achieve() { m_Achieved = true; }
	void SetReward(RewardType type, float amount);

	bool IsSelected() { return m_IsSelected; }
	bool IsAchieved() { return m_Achieved; }
	bool IsActive() const { return m_Active; }
	int GetHandle() { return m_Handle; }

protected:
	MissionType m_Type;
	int m_Handle;
	VECTOR m_Pos;
	bool m_IsSelected;
	bool m_Achieved;
	bool m_Active;

	int m_InitNum;
	int m_BorderNum;
	int m_CurrentNum;

	RewardType m_RewardType;
	float m_RewardAmount;

	UIText* m_NumText;
};

