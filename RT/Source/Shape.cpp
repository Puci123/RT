#include "Shape.h"

Shape::Shape(mu::vec3 position, double r)
    :pos(position), radius(r)
{}

Shape::Shape(double x, double y, double z, double r)
    :Shape(mu::vec3(x,y,z),r)
{}


bool CheckHitSphere(const Ray& ray, const Shape& shape, HitInfo& hitInfo)
{

    double rMin = 0.1;
    double rMax = 10000.0;

    mu::vec3 oc = ray.orgin() - shape.pos;

    double a = mu::dot(ray.dir(), ray.dir());
    double b = 2.0 * mu::dot(oc, ray.dir());
    double c = mu::dot(oc, oc) - shape.radius * shape.radius;

    double delta = b * b - 4 * a * c;

    if (delta < 0) return false;
    
    double root = ((-b - sqrt(delta)) / (2 * a));

    if (root <= rMin || root >= rMax) 
    {
        root = ((-b + sqrt(delta)) / (2 * a));
        if (root <= rMin || root >= rMax) return false;
    }

    hitInfo.t      = root;
    hitInfo.point  = ray.at(root);
    hitInfo.normal = CalcNormal(hitInfo.point, shape);

    //Check is normal is directed insied sphere or outside
    hitInfo.isFrontFace = mu::dot(hitInfo.normal, ray.dir()) < 0;

    //flip normal if it is back face
    hitInfo.normal = hitInfo.isFrontFace ? hitInfo.normal : -1 *hitInfo.normal;
    return true;

}

mu::vec3 CalcNormal(const mu::vec3& point, const Shape& shape)
{
    return (point - shape.pos) / shape.radius;
}
