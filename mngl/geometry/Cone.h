#ifndef INCLUDED_MN_GEOMETRY_CONE_H
#define INCLUDED_MN_GEOMETRY_CONE_H

#include "Cylindrical.h"

namespace Mn {

    class Cone : public Cylindrical {
    public:
        explicit Cone(
                float radius = 1.0f, float height = 1.0f,
                int radialSegments = 32, int heightSegments = 4,
                bool closed = true
        );
    };

}

#endif //INCLUDED_MN_GEOMETRY_CONE_H
