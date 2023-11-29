#pragma once

#include "MathUtility.h"
#include "Ray.h"


struct HitInfo
{
	mu::vec3 point;
	mu::vec3 normal;

	double t = 0;
	bool isFrontFace = true;

};

struct Shape
{
	double radius;
	mu::vec3 pos;
	
	Shape(mu::vec3 position, double r);
	Shape(double x, double y, double z, double r);
};

bool CheckHitSphere(const Ray& ray, const  Shape& shape, HitInfo& hitInfo);
mu::vec3 CalcNormal(const mu::vec3& point, const Shape& shape);