#include <iostream>

#include "Renderer.h"
#include "Ray.h"




inline mu::vec3 RayColor(Ray& ray, const Scean& scean) 
{
	double t = 0.5 * (ray.dir().y + 1.0);
	return (1.0 - t) * scean.colorDown + t * scean.colorUp;

}


void Rendere::Trace(Texture2D* const target, const Scean& scean)
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
	for (int32_t y = 0; y < target->GetHeight(); y++)
	{
		std::clog << "\rScanlines remaining: " << (target->GetHeight() - y) << ' ' << std::flush;

		for (int32_t x = 0; x < target->GetWidth(); x++)
		{
			mu::vec3 pixelCenter = pixelLoc + (x * pixDeltaU) + (y * pixDeltaV);
			mu::vec3 rayDir = mu::normalize(pixelCenter - camCeneter);

			Ray ray(camCeneter, rayDir);
			mu::vec3 pixelColor = RayColor(ray, scean);

			target->SetPixel(x, y, pixelColor);

		}
	}

	std::clog << "\rDone.                 \n";
}
