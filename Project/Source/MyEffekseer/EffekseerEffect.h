#pragma once

#include "DxLib.h"

class EffekseerEffect
{
public:
	EffekseerEffect();
	~EffekseerEffect();

public:
	void Step();
	void Update();
	void Fin();

	void Play(int handle);
	void Stop();

	bool IsActive() const { return m_Active; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	bool m_Active;
	int m_Handle;
	VECTOR m_Pos;
};