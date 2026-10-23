#include "Timer.h"
#include "../GameObject.h"
#include "../Component.h"

Timer::Timer(GameObject* owner) : Component(owner)
{
	m_MaxTime = 0;
	m_CurrentTime = 0;
	m_CurrentFrame = 0;
	m_Interval = 0;
	m_PrevTime = 0;

	m_CountDown = false;
	m_CountEnd = false;
	m_IsOverInterval = false;
}

Timer::~Timer()
{

}

void Timer::CountStart(int maxTime)
{
	m_MaxTime = maxTime;
	m_CurrentFrame = 0;
	m_CurrentTime = m_MaxTime;
	m_PrevTime = m_MaxTime;

	m_CountDown = true;
}

void Timer::ResetCount()
{
	m_CurrentTime = m_MaxTime;
	m_CountEnd = false;
}

void Timer::Update()
{
	if (!m_CountDown) return;

	if (m_CurrentTime <= m_MaxTime && m_CurrentTime >= 0)
	{
		m_CurrentFrame++;
	}

	if (m_CurrentFrame >= 60)
	{
		m_CurrentFrame -= 60;
		m_CurrentTime--;
	}

	int delta = m_PrevTime - m_CurrentTime;

	if (m_Interval > 0 && delta >= m_Interval)
	{
		m_IsOverInterval = true;

		m_PrevTime = m_CurrentTime;
	}

	if (m_CurrentTime <= 0)
	{
		m_CurrentTime = 0;
		m_CountDown = false;
		m_CountEnd = true;
	}
}