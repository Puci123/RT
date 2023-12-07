#include "Materials.h"
#include "DebugUtilty.h"

Ray Material::Reflect(const Ray& ray, mu::vec3& point, const mu::vec3& normal) const
{
    mu::vec3 orgin = point + normal * 0.0001; //prevent self shadowing
    mu::vec3 dir;

	switch (materialType)
	{
		case Material::Diffues:
			dir = normal + mu::ranodmOnHemisphere(normal);
			return Ray(orgin, dir);
			break;
		default:
			//INVALID MATERIAL TYPE
			ASSERT(false);
			break;
	}
}

mu::vec3 Material::GetColor()
{
    return mu::vec3();
}
