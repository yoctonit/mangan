#ifndef INCLUDED_MN_GEOMETRY_CYLINDRICAL_H
#define INCLUDED_MN_GEOMETRY_CYLINDRICAL_H

#include "Surface.h"

namespace Mn {
    class Cylindrical : public Surface {
    public:
        explicit Cylindrical(
                float radiusTop = 1.0f, float radiusBottom = 1.0f, float height = 1.0f,
                int radialSegments = 32, int heightSegments = 4,
                bool closedTop = true, bool closedBottom = true
        );

    private:
        class Equation : public SurfaceEquation {
        public:
            Equation(float radiusTop, float radiusBottom, float height);

            glm::vec3 operator()(float u, float v) const override;

        private:
            float mRadiusTop;
            float mRadiusBottom;
            float mHeight;
        };
    };

}

#endif //INCLUDED_MN_GEOMETRY_CYLINDRICAL_H
