#pragma once
#include "DxLib.h"
#include "MissionParameter.h"

class Mission
{
public:
	Mission();
	~Mission();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw(int index);
	void Fin();

public:
	MissionType GetType() { return m_Type; }
	void SetType(MissionType type) { m_Type = type; }
	void SetSelected() { m_IsSelected = true; }
	bool IsSelected() { return m_IsSelected; }
	int GetHandle() { return m_Handle; }

private:
	MissionType m_Type;
	int m_Handle;
	VECTOR m_Pos;
	bool m_IsSelected;
	bool m_Achieved;
};

