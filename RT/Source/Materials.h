#pragma once
#include "MathUtility.h"
#include "Ray.h"
#include "Texture2D.h"


struct  HitInfo;

struct Material
{
	enum class MaterialType
	{
		Diffues,
		Metalic,
		Dielectict,
		Textured
	};

	float fuzzines = 0;
	float refractionRatio = 0.5f;
	mu::vec3 allbedo;
	MaterialType materialType = MaterialType::Diffues;
	

	Ray Reflect(const Ray& ray, HitInfo& hitInfo) const;
	Texture2D* texture = nullptr;
	mu::vec3 GetColor(HitInfo& hitInfo);
};


struct HitInfo
{
	mu::vec3 point;
	mu::vec3 normal;
	mu::vec2 uv; //Used for texture maping

	Material material;

	double t = 0;
	bool isFrontFace = true;

};