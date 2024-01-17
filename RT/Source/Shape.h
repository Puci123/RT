#pragma once

#include "MathUtility.h"
#include "Ray.h"
#include "Materials.h"




struct Shape
{
	double radius;
	mu::vec3 pos;

	Material mterial;
	
	Shape(mu::vec3 position, double r, Material mat);
	Shape(double x, double y, double z, double r,  Material mat);
};

bool CheckHitSphere(const Ray& ray, const Shape& shape, HitInfo& hitInfo);
mu::vec3 CalcNormal(const mu::vec3& point, const Shape& shape);