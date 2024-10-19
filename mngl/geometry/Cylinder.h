#ifndef INCLUDED_MN_GEOMETRY_CYLINDER_H
#define INCLUDED_MN_GEOMETRY_CYLINDER_H

#include "Cylindrical.h"

namespace Mn {

    class Cylinder : public Cylindrical {
    public:
        explicit Cylinder(
                float radius = 1.0f, float height = 1.0f,
                int radialSegments = 32, int heightSegments = 4,
                bool closed = true
        );
    };

}

#endif //INCLUDED_MN_GEOMETRY_CYLINDER_H
