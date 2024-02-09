#pragma once
#include "Texture2D.h"
#include "Scean.h"

namespace Rendere 
{
	struct Camera
	{
		double aspectRatio		= 0;
		double focalLenght		= 0;
		double viwiePortHeight	= 0;
		double viwiePortWidth	= 0;
		double vFov				= 0;
		mu::vec3 camCeneter		= mu::vec3{ 0,0,0 };
		mu::vec3 viewportU		= mu::vec3{ 0,0,0 };
		mu::vec3 viewportV		= mu::vec3{ 0,0,0 };
		mu::vec3 pixelDeltaU	= mu::vec3{ 0,0,0 };
		mu::vec3 pixelDeltaV	= mu::vec3{ 0,0,0 };
		mu::vec3 upperLeftPixel = mu::vec3{ 0,0,0 };

		mu::vec3 lookFrom = mu::vec3{ 0,0, 0};
		mu::vec3 lookAt   = mu::vec3{ 0,0,0 };
		mu::vec3 up		  = mu::vec3{ 0,0,0 };

		mu::vec3 u = mu::vec3{ 0,0,0 };
		mu::vec3 v = mu::vec3{ 0,0,0 };
		mu::vec3 w = mu::vec3{ 0,0,0 };
		
	};


	void   Bake(int32_t screanWidth, Rendere::Camera& cam, int32_t screanHeight);
	void   Trace(Texture2D& target, Scean& scean, Rendere::Camera& cam, int32_t maxDepth, int32_t samplePerPixel, uint32_t start, uint32_t numberOfline);
	void   AlphaCorrect(Texture2D* const target);
}
