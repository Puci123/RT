#include "Shape.h"

Shape::Shape(mu::vec3 position ,double r, Material mat)
    :pos(position), radius(r), mterial(mat)
{}

Shape::Shape(double x, double y, double z, double r, Material mat)
    :Shape(mu::vec3(x,y,z),r,mat)
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

    hitInfo.t        = root;
    hitInfo.point    = ray.at(root);
    hitInfo.normal   = CalcNormal(hitInfo.point, shape);
    hitInfo.material = shape.mterial;

    //Check is normal is directed insied sphere or outside
    hitInfo.isFrontFace = mu::dot(hitInfo.normal, ray.dir()) < 0;

    //flip normal if it is back face
    hitInfo.normal = hitInfo.isFrontFace ? hitInfo.normal : -1 *hitInfo.normal;

    //Set uv cords for texture sampling
    double theta = acos(-hitInfo.point.y);
    double phi = atan2(-hitInfo.point.z, hitInfo.point.x) + mu::pi;

    hitInfo.uv.x = phi / (2 * mu::pi);
    hitInfo.uv.y = theta / mu::pi;


    return true;

}

mu::vec3 CalcNormal(const mu::vec3& point, const Shape& shape)
{
    return (point - shape.pos) / shape.radius;
}
