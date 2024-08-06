#include "c_with_classes.h"
#include "vector_math.h"
#include "matrix_transformations.h"
#include "intersections.h"
#include "ppm.h"

void ray_sphere_intersection(PPM& ppm, const Vector& camera, const Sphere& sphere,const Matrix& transform_matrix, const str& color)
{
    for (int col{0}; col < ppm.image_size; ++col)
    {
        for (int row{0}; row < ppm.image_size; ++row)
        {
            Vector direction{cast<flt>(row) - ppm.image_size / 2, cast<flt>(col) - ppm.image_size / 2, -250};
            Ray ray{camera, direction};

            if (hit(intersect(sphere, transform(ray,transform_matrix))) >= 0)
            {
                ppm(row, col) = color;
            }
        }
    }
}
int main()
{
    PPM ppm{1024};
    const Vector camera{point(0, 0, 0)};
    const Sphere sphere{{0, 0, -10}, 5};

    const Matrix sphere1 {translation(-5,20,0)*scaling(1,3,1)};
    ray_sphere_intersection(ppm,camera,sphere,sphere1,"0 0 0");
    const Matrix sphere2 {translation(5,-5,0)*scaling(2,1,1)};
    ray_sphere_intersection(ppm,camera,sphere,sphere2,"255 0 0");
    const Matrix sphere3 {translation(0,7,0)*scaling(2,5,1)};
    ray_sphere_intersection(ppm,camera,sphere,sphere3,"0 255 0");
    const Matrix sphere4 {translation(2,2,3)*scaling(4,0.4,1)};
    ray_sphere_intersection(ppm,camera,sphere,sphere4,"0 0 255");
    ppm.save("yey");
    return 0;
}
