#ifndef INCLUDED_MN_GEOMETRY_BOX_GEOMETRY_H
#define INCLUDED_MN_GEOMETRY_BOX_GEOMETRY_H

#include "Geometry.h"

namespace Mn {

    class Box : public Geometry {
    public:
        void Create(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
    };

}

#endif //INCLUDED_MN_GEOMETRY_BOX_GEOMETRY_H
