#ifndef _Object_H
#define _Object_H

#include "MathUtility.h"
#include "Color.h"

class Object 
{	
	public:
	
	Object ();
	virtual Color getColor () 
	{ 
	    return Color (0.0, 0.0, 0.0, 0); 
    }
	
	virtual vec3 getNormalAt(vec3 intersection_position) 
	{
		return vec3 (0, 0, 0);
	}
	
	virtual double findIntersection(Ray ray) 
	{
		return 0;
	}
	
};

Object::Object () {}

#endif
