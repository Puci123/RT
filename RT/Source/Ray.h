#pragma once
#include "MathUtility.h"
#include <iostream>
using namespace std;


class Ray
{
public:
		Ray(mu::vec3 orgin, mu::vec3 dir) : m_Orgin(orgin), m_Dir(dir) {}
		~Ray() {}

		inline mu::vec3 orgin()				const { return m_Orgin; }
		inline mu::vec3 dir()				const { return m_Dir; }
		inline mu::vec3 at(float dist)		const { return m_Orgin + m_Dir * dist; }	//Return positon after traveling certian distance 


private:
		mu::vec3 m_Orgin;
		mu::vec3 m_Dir;

};
#endif // Ray_h
