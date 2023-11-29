#include "Scean.h"

Scean::Scean()
{
}

Scean::~Scean()
{
}

bool Scean::CheckHit(const Ray& ray, HitInfo& hitInfo) const
{

	HitInfo temp;
	double closest = 100000; //TODO: 
	temp.t = closest;
	bool hit = false;


	for (size_t i = 0; i < M_Shapes.size(); i++)
	{
		if (CheckHitSphere(ray,M_Shapes[i], temp) && temp.t < closest)
		{
			hit = true;
			closest = temp.t;
			
			hitInfo.t = temp.t;
			hitInfo.point = temp.point;
			hitInfo.normal = temp.normal;
			hitInfo.isFrontFace = temp.isFrontFace;
		}
	}

	return hit;
}
