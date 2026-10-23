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
	void CountStart(int maxTime);
	void ResetCount();
	void SetInterval(int interval) { m_Interval = interval; }
	void SetIsOverInterval(bool isOver) { m_IsOverInterval = isOver; }

	int GetCurrentSecond() const { return m_CurrentTime % 60; }
	int GetCurrentMinute() const { return m_CurrentTime / 60; }
	bool IsCountEnd() const { return m_CountEnd; }
	bool IsOverInterval() const { return m_IsOverInterval; }

private:
	int m_MaxTime;
	int m_CurrentTime;
	int m_CurrentFrame;
	int m_Interval;
	int m_PrevTime;

	bool m_CountDown;
	bool m_CountEnd;
	bool m_IsOverInterval;
};