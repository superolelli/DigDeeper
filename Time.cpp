#include "Time.hpp"
#include <iostream>



CTime::CTime()
{
	m_elapsed = seconds(0);
	m_current = seconds(0);
	m_lastTime = seconds(0);
	m_clock.restart();
}




void CTime::Update()
{
	m_current += m_clock.getElapsedTime();
	m_elapsed = m_clock.restart();
	m_lastTime = seconds(0);
}


Time CTime::GetElapsedTimeThisFrame()
{
	Time returnTime;
	returnTime = m_clock.getElapsedTime() - m_lastTime;
	m_lastTime = m_clock.getElapsedTime();
	return returnTime;
}