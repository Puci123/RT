#include <iostream>

#include "Renderer.h"
#include "Shape.h"
#include "Ray.h"





inline mu::vec3 RayColor(const Ray& ray, const Scean& scean, int32_t depth) 
{
	
	if (depth < 0) return mu::vec3(0, 0, 0);

	HitInfo hitInfo;

	if (scean.CheckHit(ray,hitInfo))
	{
		mu::vec3 reflectionDir = mu::ranodmOnHemisphere(hitInfo.normal);
		Ray reflected = hitInfo.material.Reflect(ray, hitInfo);

		return  hitInfo.material.GetColor(hitInfo)  * RayColor(reflected, scean ,depth - 1);
	}
	else
	{
		double t = 0.5 * (ray.dir().y + 1.0);
		return (1.0 - t) * scean.M_ColorDown + t * scean.M_ColorUp;
	}

}


void  Rendere::Bake(int32_t screanWidth, Rendere::Camera& cam, int32_t screanHeight)
{
	
	cam.lookFrom   = mu::vec3{-2,2,1};
	cam.lookAt	   = mu::vec3{ 0,0,-1 };
	cam.up		   = mu::vec3{ 0,1,0 };
	cam.camCeneter = cam.lookFrom;


	cam.aspectRatio	= static_cast<double>(screanWidth) / static_cast<double>(screanHeight);
	cam.focalLenght = mu::lenght(cam.lookFrom - cam.lookAt);
	cam.vFov				= 90;

	double theta = mu::deg2rad(cam.vFov);
	double h = tan(theta / 2);


	cam.viwiePortHeight		= 2 * h * cam.focalLenght;
	cam.viwiePortWidth		= cam.viwiePortHeight * cam.aspectRatio;

	cam.w = mu::normalize(cam.lookFrom - cam.lookAt);
	cam.u = mu::normalize(mu::cross(cam.up, cam.w));
	cam.v = mu::cross(cam.w, cam.u);

	cam.viewportU			= cam.viwiePortWidth * cam.u;
	cam.viewportV			= cam.viwiePortHeight * (-1 * cam.v);

	cam.pixelDeltaU			= cam.viewportU / static_cast<double>(screanWidth);
	cam.pixelDeltaV			= cam.viewportV / static_cast<double>(screanHeight);
	cam.upperLeftPixel		= cam.camCeneter - (cam.focalLenght * cam.w) - cam.viewportU / 2 - cam.viewportV / 2;


}

void Rendere::Trace(Texture2D& target,  Scean& scean, static Camera& cam ,int32_t maxDepth, int32_t samplePerPixel,uint32_t start, uint32_t stop)
{
	//Curent pixel location
	mu::vec3 pixelLoc = cam.upperLeftPixel + 0.5 * (cam.pixelDeltaU + cam.pixelDeltaV);
	
	//Cast Rays
	for (uint32_t y = start; y < stop; y++)
	{
		
		for (uint32_t x = 0; x < target.GetWidth(); x++)
		{
			
			mu::vec3 pixelColor = mu::vec3(0, 0, 0);

			for (int32_t sample = 0; sample < samplePerPixel; sample++)
			{
			

				mu::vec3 sampleSquer = cam.pixelDeltaU * (-0.5 + mu::randomDouble()) + cam.pixelDeltaV * (-0.5 + mu::randomDouble());
				mu::vec3 pixelCenter = pixelLoc + (x * cam.pixelDeltaU) + (y * cam.pixelDeltaV) + sampleSquer;

				mu::vec3 rayDir = mu::normalize(pixelCenter - cam.camCeneter);

				Ray ray(cam.camCeneter, rayDir);
				pixelColor = pixelColor + RayColor(ray, scean, maxDepth);

			}

			target.SetPixel(x, y, pixelColor / static_cast<double>(samplePerPixel));
		}
	}
}


void Rendere::AlphaCorrect(Texture2D* const target)
{
	for (uint32_t y = 0; y < target->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < target->GetWidth(); x++)
		{
			mu::vec3 temp = static_cast<mu::vec3>(target->GetPixel(x, y));
			temp = mu::vec3(sqrt(temp.x), sqrt(temp.y), sqrt(temp.z));

			target->SetPixel(x, y, temp);
		}
	}
}
