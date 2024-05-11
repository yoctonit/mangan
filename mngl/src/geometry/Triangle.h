#ifndef INCLUDED_MN_GEOMETRY_TRIANGLE_H
#define INCLUDED_MN_GEOMETRY_TRIANGLE_H

#include <vector>
#include <cmath>

namespace Mn::geometry {

    // center mass in (0,0)
    std::vector<float> equilateral_triangle(float side) {
        float tmp = side * std::sqrt(3.0f) / 6.0f;
        float half_side = 0.5f * side;
        return {
                -half_side, -tmp, 0.0f,
                half_side, -tmp, 0.0f,
                0.0f, 2.0f * tmp, 0.0f,
        };
    }

}

#endif //INCLUDED_MN_GEOMETRY_TRIANGLE_H
