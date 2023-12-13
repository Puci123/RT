#include "Materials.h"
#include "DebugUtilty.h"

//==================== HELPER FUNCTIONS ====================// 



inline double ReflactencAprox(double cosinePhi, double regIx)
{
	// Use Schlick's approximation for reflectance.
	double r0 = (1 - regIx) / (1 + regIx);
	r0 = r0 * r0;

	return r0 + (1 - r0) * pow((1 - cosinePhi), 5);
}

inline mu::vec3 reflect(const mu::vec3& a, const mu::vec3& normal)
{
	return a - 2 * dot(a, normal) * normal;
}



inline mu::vec3 refract(const mu::vec3& v, const mu::vec3& normal, double etaiOverTheta)
{
	mu::vec3 inversV = -1.0 * v;

	double cosTheta = fmin(dot(inversV, normal), 1.0);
	mu::vec3 rOutPrep = etaiOverTheta * (v + cosTheta * normal);
	mu::vec3 rOutParrarel = -sqrt(fabs(1.0 - mu::lengthSquared(rOutPrep))) * normal;

	return rOutPrep + rOutParrarel;
}

//==========================================================//

Ray Material::Reflect(const Ray& ray, HitInfo& hitInfo) const
{
    mu::vec3 orgin = hitInfo.point + hitInfo.normal * 0.0001; //prevent self shadowing
    mu::vec3 dir;

	switch (materialType)
	{
		case MaterialType::Diffues:
			dir = hitInfo.normal + mu::ranodmOnHemisphere(hitInfo.normal);
			return Ray(orgin, dir);
		case MaterialType::Metalic:
			dir = ray.dir() - 2 * mu::dot(ray.dir(), hitInfo.normal) * hitInfo.normal + fuzzines * mu::randomUnitVector();
			return Ray(orgin, dir);
		case MaterialType::Dielectict:
			double refractionRatio = hitInfo.isFrontFace ? (1.0 / hitInfo.material.refractionRatio) : hitInfo.material.refractionRatio;

			mu::vec3 unitDir = mu::normalize(ray.dir());

			double cosTheta = fmin(dot(-1.0 * unitDir, hitInfo.normal), 1.0);
			double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

			if ((refractionRatio * sinTheta > 1.0) || ReflactencAprox(cosTheta, refractionRatio) > mu::randomDouble())
				return Ray(hitInfo.point, reflect(unitDir, hitInfo.normal));
			else
				return Ray(hitInfo.point, refract(unitDir, hitInfo.normal, refractionRatio));


		//INVALID MATERIAL TYPE
		ASSERT(false);
		break;
	}
}

mu::vec3 Material::GetColor()
{
    return mu::vec3();
}
