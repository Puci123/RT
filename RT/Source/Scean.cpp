#include "Scean.h"
#include "Interval.h"

Scean::Scean()
{
}

Scean::~Scean()
{
}

bool Scean::CheckHit(const Ray& ray, HitInfo& hitInfo) const
{

	HitInfo temp;
	Interval interval;

	//double closest = 100000; //TODO: INTERVALS 
	temp.t = mu::inifinty;
	bool hit = false;


	for (size_t i = 0; i < M_Shapes.size(); i++)
	{
		if (CheckHitSphere(ray,M_Shapes[i], temp) && interval.IsIn(temp.t))
		{
			hit = true;
			interval.SetMax(temp.t);
			
			hitInfo.t = temp.t;
			hitInfo.point = temp.point;
			hitInfo.normal = temp.normal;
			hitInfo.isFrontFace = temp.isFrontFace;
			hitInfo.material = temp.material;
		}
	}

	return hit;
}
