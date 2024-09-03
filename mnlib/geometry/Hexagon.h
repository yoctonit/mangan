#ifndef INCLUDED_MN_GEOMETRY_HEXAGON_H
#define INCLUDED_MN_GEOMETRY_HEXAGON_H

#include "Polygon.h"

namespace Mn {

    class Hexagon : public Polygon {
    public:
        explicit Hexagon(float radius = 1.0f);
    };

}

#endif //INCLUDED_MN_GEOMETRY_HEXAGON_H
