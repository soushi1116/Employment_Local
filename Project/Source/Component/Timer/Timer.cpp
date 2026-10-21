#include "Timer.h"
#include "../GameObject.h"
#include "../Component.h"

Timer::Timer(GameObject* owner) : Component(owner)
{
	m_StartTime = 0;
	m_MaxTime = 0;
	m_CurrentTime = 0;

	m_CountDown = false;
	m_CountEnd = false;
}

Timer::~Timer()
{

}

void Timer::CountStart(float maxSecond)
{
	m_StartTime = GetNowCount();
	m_MaxTime = static_cast<int>(maxSecond * 1000.0f);
	m_CurrentTime = m_MaxTime;

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

	m_CurrentTime = m_MaxTime - (GetNowCount() - m_StartTime);

	if (m_CurrentTime < 0)
	{
		m_CurrentTime = 0;
		m_CountDown = false;
		m_CountEnd = true;
	}
}