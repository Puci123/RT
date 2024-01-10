#pragma once
#include "MathUtility.h"


class Interval
{
	public:
		Interval(double min, double max) : m_Min(min), m_Max(max) {}
		Interval() : Interval(mu::epsilon, mu::inifinty){}

		~Interval() {}

		inline bool IsIn(double val) const  { return (val >= m_Min && val <= m_Max); }
		inline double GetMax()		 const	{ return m_Max; }
		inline double GetMin()       const  { return m_Min; }

		inline void SetMin(double value) { m_Min = value; }
		inline void SetMax(double value) { m_Max = value; }


	private:
		double m_Min;
		double m_Max;
};

