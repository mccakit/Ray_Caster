#include "c_with_classes.h"
#include "vector_math.h"
#include "matrix_transformations.h"
#include "intersections.h"
#include "ppm.h"


int main()
{
    PPM ppm{1024};
    const Sphere sphere{{0, 0, -10}, 5};
    const Vector camera{point(0, 0, 0)};
    for (int col{0}; col < ppm.image_size; ++col)
    {
        for (int row{0}; row < ppm.image_size; ++row)
        {
            Vector direction{cast<flt>(row) - ppm.image_size / 2, cast<flt>(col) - ppm.image_size / 2, -500};
            Ray ray{camera, direction};
            if (hit(intersect(sphere, ray)) >= 0)
            {
                ppm(row, col) = "0 0 0";
            }
        }
    }
    ppm.save("yey");
    return 0;
}
