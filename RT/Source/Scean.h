#pragma once
#include<vector>

#include "MathUtility.h"
#include "Shape.h"

class Scean
{
	public:
		Scean();
		~Scean();

		bool CheckHit(const Ray& ray, HitInfo& hitInfo) const;

		//Scean backgorund color
		mu::vec3 M_ColorDown = mu::vec3(1.0, 1.0, 1.0);
		mu::vec3 M_ColorUp   = mu::vec3(0.5, 0.7, 1.0);
		std::vector<Shape> M_Shapes;
};