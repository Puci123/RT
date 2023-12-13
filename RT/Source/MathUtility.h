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

	struct vec4
	{
		float x, y, z, w;

		vec4(float _x, float _y, float _z, float _w);
		vec4();
	};

	struct vec3
	{
		double x, y, z;
		
		vec3();
		vec3(double _x, double _y, double _z);
		vec3(vec4 v);

	};

	



	//================================= vec3 opeartors =================================//
	
	inline vec3 operator+(const vec3& a, const vec3& b)
	{
		return vec3{ a.x + b.x, a.y + b.y, a.z + b.z };
	}

	inline vec3 operator-(const vec3& a, const vec3& b)
	{
		return vec3{ a.x - b.x, a.y - b.y, a.z - b.z };
	}

	inline vec3 operator*(const vec3& a, double b)
	{
		return vec3{ a.x * b, a.y * b, a.z * b };
	}

	inline vec3 operator*(double b, const vec3& a)
	{
		return vec3{ a.x * b, a.y * b, a.z * b };
	}

	inline vec3 operator*(const vec3& a, const vec3& b) 
	{
		return vec3{ a.x * b.x, a.y * b.y, a.z * b.z };
	}

	inline vec3 operator/(const vec3& a, double b)
	{
		return a * (1.0 / b);
	}

	
	inline double lenght(const vec3& a)
	{
		return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	}

	inline double lengthSquared(const vec3& a)
	{
		return a.x * a.x + a.y * a.y + a.z * a.z;
	}

	inline vec3 normalize(const vec3& a)
	{
		return a / lenght(a);
	}

	inline double dot(const vec3& a, const vec3& b) 
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}



	//================================= RANDOM FUNCTIONS =================================//

	inline double randomDouble()
	{
		return (static_cast<double>(rand()) / RAND_MAX);
	}

	inline double randomDouble(double min, double max)
	{
		return min + (max - min) * randomDouble();
	}

	inline vec3 randomVector(double min, double max)
	{
		return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

	inline vec3 randomInUnitSphere()
	{
		//TODO: 
		while (true)
		{
			vec3 p = randomVector(-1, 1);

			if (lenght(p) < 1) return p;

		}
	}

	inline vec3 randomUnitVector()
	{
		return normalize(randomInUnitSphere());
	}

	inline vec3 ranodmOnHemisphere(const vec3& normal)
	{
		vec3 unitVec = randomUnitVector();

		if (dot(unitVec, normal) > 0.0) return unitVec;

		return -1 * unitVec;

	}

}