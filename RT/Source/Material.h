#pragma once
#include "MathUtility.h"


class Material
{
	public:
		Material(mu::vec3 color);
		~Material();

	private:
		mu::vec3 m_Color;

};

