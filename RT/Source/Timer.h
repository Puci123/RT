#pragma once
#include<chrono>
#include<iostream>

#include "DebugUtilty.h"


class Timer
{
	public:
		Timer();
		~Timer();

		void Start();
		void Stop();
		std::string Print() const;
	


	private:
		std::chrono::steady_clock::time_point m_StartPoint;
		std::chrono::steady_clock::time_point m_EndPoint;

		float m_Diuration = -1.0;

};


std::ostream& operator<< (std::ostream& stream, const Timer& matrix);
