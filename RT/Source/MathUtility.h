#pragma once
#include <random>
#include <limits.h>

namespace mu
{
	struct vec2
	{
		double x, y;

		vec2(double x, double y);
		vec2();
			
	};

	struct vec3
	{
		double x, y, z;
		
		vec3(float _x, float _y, float _z);
		vec3();

	};

	struct vec4
	{
		float x, y, z, w;

		vec4(float _x, float _y, float _z, float _w);
		vec4();
	};

	//================================= RANDOM FUNCTIONS =================================//

	inline double randomDouble() 
	{
		return (static_cast<double>(rand()) / RAND_MAX);
	}

	inline double randomDouble(double min, double max) 
	{
		return min + (max - min) * randomDouble();
	}

	

}