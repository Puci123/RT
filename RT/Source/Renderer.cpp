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
		return 0.5f * RayColor(Ray(hitInfo.point, reflectionDir), scean ,depth - 1);
	}
	else
	{
		double t = 0.5 * (ray.dir().y + 1.0);
		return (1.0 - t) * scean.M_ColorDown + t * scean.M_ColorUp;
	}

}


void Rendere::Trace(Texture2D* const target, const Scean& scean, int32_t maxDepth, int32_t samplePerPixel)
{
	double aspectRatio		= static_cast<double>(target->GetWidth()) / static_cast<double>(target->GetHeight());
	
	//Camera Parameters
	double focalLenght		= 1;
	double viwiePortHeight	= 2.0;
	double viwiePortWidth	= viwiePortHeight * aspectRatio;
	mu::vec3 camCeneter		= mu::vec3{ 0,0,0 };
	mu::vec3 viewportU		= mu::vec3{ viwiePortWidth,0,0 };
	mu::vec3 viewportV		= mu::vec3{ 0,-viwiePortHeight,0 };

	//Calculate the horizontal and vertical delta vectors from pixel to pixel.
	mu::vec3 pixDeltaU = viewportU / static_cast<double>(target->GetWidth());
	mu::vec3 pixDeltaV = viewportV / static_cast<double>(target->GetHeight());

	//Upper left pixel location
	mu::vec3 viwiePortUpperLeft = camCeneter - mu::vec3(0, 0, focalLenght) - viewportU / 2 - viewportV / 2;
	mu::vec3 pixelLoc			= viwiePortUpperLeft + 0.5 * (pixDeltaU + pixDeltaV);

	std::cout << "Rendering image with size: " << target->GetWidth() << "x" << target->GetHeight() << std::endl << std::endl;
	
	//Cast Rays
	for (uint32_t y = 0; y < target->GetHeight(); y++)
	{
		std::clog << "\rScanlines remaining: " << (target->GetHeight() - y) << ' ' << std::flush;

		for (uint32_t x = 0; x < target->GetWidth(); x++)
		{
			
			mu::vec3 pixelColor = mu::vec3(0, 0, 0);

			for (int32_t sample = 0; sample < samplePerPixel; sample++)
			{
			

				mu::vec3 sampleSquer = pixDeltaU * (-0.5 + mu::randomDouble()) + pixDeltaV * (-0.5 + mu::randomDouble());
				mu::vec3 pixelCenter = pixelLoc + (x * pixDeltaU) + (y * pixDeltaV) + sampleSquer;

				mu::vec3 rayDir = mu::normalize(pixelCenter - camCeneter);

				Ray ray(camCeneter, rayDir);
				pixelColor = pixelColor + RayColor(ray, scean, maxDepth);

			}

			target->SetPixel(x, y, pixelColor / static_cast<double>(samplePerPixel));
		}
	}

	std::clog << "\rDone.                 \n";
}

void Rendere::AlphaCorrect(Texture2D* const target)
{
	for (int32_t y = 0; y < target->GetHeight(); y++)
	{
		for (int32_t x = 0; x < target->GetWidth(); x++)
		{
			mu::vec3 temp = static_cast<mu::vec3>(target->GetPixel(x, y));
			temp = mu::vec3(sqrt(temp.x), sqrt(temp.y), sqrt(temp.z));

			target->SetPixel(x, y, temp);
		}
	}
}
