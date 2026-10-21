#pragma once

#include "DxLib.h"
#include <memory>
#include "../Component.h"

class GameObject;

class Timer : public Component
{
public:
	Timer(GameObject* owner);
	~Timer();

public:
	void Update() override;

public:
	void CountStart(float maxSecond);
	void ResetCount();

	int GetCurrentMilliSecond() const { return m_CurrentTime; }
	int GetCurrentSecond() const { return (m_CurrentTime / 1000) % 60; }
	int GetCurrentMinute() const { return (m_CurrentTime / 1000) / 60; }
	bool IsCountEnd() const { return m_CountEnd; }

private:
	int m_StartTime;
	int m_MaxTime;
	int m_CurrentTime;

	bool m_CountDown;
	bool m_CountEnd;
};