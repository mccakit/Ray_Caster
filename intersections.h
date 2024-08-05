#pragma once
#include "c_with_classes.h"
#include "vector_math.h"

struct Ray
{
    Vector origin{};
    Vector direction{};

    Ray(const Vector& origin, const Vector& direction):
        origin{origin},
        direction{direction}
    {
    }
};

Vector position(const Ray& ray, const flt& time)
{
    return ray.origin + ray.direction * time;
}

struct Sphere
{
    Sphere(const Vector& origin, const flt& radius):
        origin{origin},
        radius{radius}
    {
    }

    Vector origin{};
    flt radius{};
};

arr<flt> intersect(const Sphere& sphere, Ray ray)
{
    ray.origin.elements.pop();
    const Vector w{ray.origin - sphere.origin};
    const Vector v = {ray.direction};
    const flt r {sphere.radius};
    const flt a {dotproduct(v, v)};
    const flt b {2* dotproduct(v, w)};
    const flt c {dotproduct(w, w) - pow(r, 2)};
    const flt discriminant{pow(b, 2) - 4 * a * c};
    if (discriminant < 0)
    {
        return {};
    }
    if (discriminant == 0)
    {
        return {-b/(2*a)};
    }
    else
    {
        return {(-b-sqrt(discriminant))/(2*a), (-b+sqrt(discriminant))/(2*a)};
    }
}
flt hit(const arr<flt>& intersections)
{
    if(intersections.empty())
    {
        return -1;
    }
    if(intersections.size() == 1 and intersections[0]>=0)
    {
        return intersections[0];
    }
    if(intersections.size() == 2)
    {
        flt least{INT_MAX};
        for (auto& item: intersections)
        {
            if(item > 0 and item < least)
            {
                least = item;
            }
        }
        if(least == INT_MAX)
        {
            return -1;
        }
        return least;
    }
}
Ray transform(Ray ray,const Matrix& matrix)
{
    ray.direction = matrix*ray.direction;
    ray.origin = matrix*ray.origin;
    return ray;
}
