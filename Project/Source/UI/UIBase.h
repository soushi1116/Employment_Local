#pragma once
#include "DxLib.h"
#include "UIParameter.h"

class UIBase
{
public:
	UIBase();
	~UIBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

public:
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetType(UIType type) { m_Type = type; }
	void SetName(UIName name) { m_Name = name; }
	void SetActive(bool active) { m_Active = active; }

	UIName GetName() { return m_Name; }


protected:
	VECTOR m_Pos;
	int m_Handle;
	UIType m_Type;
	UIName m_Name;
	bool m_Active;
};