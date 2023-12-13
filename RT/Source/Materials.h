#pragma once
#include "MathUtility.h"
#include "Ray.h"



struct  HitInfo;

struct Material
{
	enum class MaterialType
	{
		Diffues,
		Metalic,
		Dielectict
	};

	float fuzzines = 0;
	float refractionRatio = 0.5f;
	mu::vec3 allbedo;
	MaterialType materialType;
	

	Ray Reflect(const Ray& ray, HitInfo& hitInfo) const;
	mu::vec3 GetColor();
};


struct HitInfo
{
	mu::vec3 point;
	mu::vec3 normal;

	Material material;

	double t = 0;
	bool isFrontFace = true;

};