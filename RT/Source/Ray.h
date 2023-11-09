#ifndef Ray_h
#define Ray_h

#include "MathUtility.h"
#include <iostream>
using namespace std;

class Ray
{
public:
    Ray(){}
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction){}

    point3 origin() const {return orig;}
    vec3 direction() const {return dir;}
    point3 at(double t)const
    {
        return orig +t*dir;
    }

private:
    point3 orig;
    vec3 dir;

};
#endif // Ray_h
