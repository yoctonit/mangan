#ifndef INCLUDED_MN_GEOMETRY_SPHERE_H
#define INCLUDED_MN_GEOMETRY_SPHERE_H

#include "Ellipsoid.h"


namespace Mn {

    class Sphere : public Ellipsoid {
    public:
        explicit Sphere(float radius = 1.0f, int radiusSegments = 32, int heightSegments = 16);
    };

}

#endif //INCLUDED_MN_GEOMETRY_SPHERE_H
