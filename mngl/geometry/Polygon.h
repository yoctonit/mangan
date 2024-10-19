#ifndef INCLUDED_MN_GEOMETRY_POLYGON_H
#define INCLUDED_MN_GEOMETRY_POLYGON_H

#include "Geometry.h"

namespace Mn {

    class Polygon : public Geometry {
    public:
        explicit Polygon(int sides = 3, float radius = 1.0f);
    private:
        void Create(int sides = 3, float radius = 1.0f);
    };

}

#endif //INCLUDED_MN_GEOMETRY_POLYGON_H
