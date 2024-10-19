#ifndef INCLUDED_MN_GEOMETRY_PYRAMID_H
#define INCLUDED_MN_GEOMETRY_PYRAMID_H

#include "Cylindrical.h"

namespace Mn {

    class Pyramid : public Cylindrical {
    public:
        explicit Pyramid(
                float radius = 1.0f, float height = 1.0f,
                int sides = 4, int heightSegments = 4,
                bool closed = true
        );
    };

}

#endif //INCLUDED_MN_GEOMETRY_PYRAMID_H
