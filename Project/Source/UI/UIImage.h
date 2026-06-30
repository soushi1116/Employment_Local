#pragma once
#include "DxLib.h"
#include "UIParameter.h"

class UIImage
{
public:
	UIImage();
	~UIImage();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetType(UIType type) { m_Type = type; }

protected:
	VECTOR m_Pos;
	int m_Handle;
	UIType m_Type;
};