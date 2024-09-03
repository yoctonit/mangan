#ifndef INCLUDED_MN_GEOMETRY_PRISM_H
#define INCLUDED_MN_GEOMETRY_PRISM_H

#include "Cylindrical.h"

namespace Mn {

    class Prism : public Cylindrical {
    public:
        explicit Prism(
                float radius = 1.0f, float height = 1.0f,
                int sides = 6, int heightSegments = 4,
                bool closed = true
        );
    };

}

#endif //INCLUDED_MN_GEOMETRY_PRISM_H
