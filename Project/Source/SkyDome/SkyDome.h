#pragma once
#include "DxLib.h"

class SkyDome
{
public:
	SkyDome();
	~SkyDome();

public:
	void Load();
	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};