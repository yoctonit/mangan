#ifndef INCLUDED_MN_GEOMETRY_ELLIPSOID_H
#define INCLUDED_MN_GEOMETRY_ELLIPSOID_H

#include "Surface.h"

namespace Mn {

    class Ellipsoid : public Surface {
    public:
        explicit Ellipsoid(
                float width = 1.0f, float height = 1.0f, float depth = 1.0f,
                int radiusSegments = 32, int heightSegments = 16
        );

    private:
        class Equation : public SurfaceEquation {
        public:
            Equation(float width, float height, float depth);

            glm::vec3 operator()(float u, float v) const override;

        private:
            float mWidth;
            float mHeight;
            float mDepth;
        };

    };

}

#endif //INCLUDED_MN_GEOMETRY_ELLIPSOID_H
