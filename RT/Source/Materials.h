#pragma once
#include "MathUtility.h"
#include "Ray.h"


struct Material
{
	enum class MaterialType
	{
		Diffues,
		Metalic
	};

	float fuzzines = 0;
	mu::vec3 allbedo;
	MaterialType materialType;
	

	Ray Reflect(const Ray& ray, mu::vec3& point, const mu::vec3& normal) const;
	mu::vec3 GetColor();
};

