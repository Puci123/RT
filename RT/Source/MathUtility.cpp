#include "MathUtility.h"


mu::vec4::vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

mu::vec4::vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}


mu::vec3::vec3(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

mu::vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

mu::vec2::vec2(double _x, double _y)
{
	x = _x;
	y = _y;
}

mu::vec2::vec2()
{
	x = 0;
	y = 0;
}
