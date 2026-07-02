#pragma once
#include "DxLib.h"

class Cursor
{
public:
	Cursor();
	~Cursor();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	VECTOR GetPos() { return m_Pos; }
	float GetScale() { return m_Scale; }
	int GetHandle() { return m_Handle; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetMaxPos(VECTOR pos) { m_MaxPos = pos; }
	void SetMinPos(VECTOR pos) { m_MinPos = pos; }
	void SetScale(float scale) { m_Scale = scale; }
	void SetMoveDiff(float diff) { m_MoveDiff = diff; }

private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_MaxPos;
	VECTOR m_MinPos;
	VECTOR m_Move;
	float m_Scale;
	float m_MoveDiff;
	bool m_IsMoving;
};