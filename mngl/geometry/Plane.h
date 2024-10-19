#ifndef INCLUDED_MN_GEOMETRY_PLANE_H
#define INCLUDED_MN_GEOMETRY_PLANE_H

#include "Surface.h"

namespace Mn {

    class Plane : public Surface {
    public:
        explicit Plane(
                float width = 1.0f, float height = 1.0f,
                int widthSegments = 8, int heightSegments = 8
        );

    private:
        class Equation: public SurfaceEquation {
        public:
            glm::vec3 operator()(float u, float v) const override;
        };
    };

}

#endif //INCLUDED_MN_GEOMETRY_PLANE_H
