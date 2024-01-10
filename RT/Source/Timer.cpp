#include<string>
#include "Timer.h"


Timer::Timer(){}

Timer::~Timer(){}



void Timer::Start()
{

	m_StartPoint = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
	m_EndPoint  = std::chrono::high_resolution_clock::now();
	m_Diuration = std::chrono::duration_cast<std::chrono::microseconds>(m_EndPoint - m_StartPoint).count() / 1000000.f;

}

std::string Timer::Print() const
{
	if (m_Diuration < 0) 
	{
		return " Timer still counting";
		
	}

	return std::to_string(m_Diuration);

}

std::ostream& operator<< (std::ostream& stream, const Timer& timer)
{
	return (stream << timer.Print() << " s");
}
