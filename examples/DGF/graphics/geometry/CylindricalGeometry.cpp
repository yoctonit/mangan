#include <cmath>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>

#include "CylindricalGeometry.h"
#include "PolygonGeometry.h"

CylindricalGeometry::CylindricalGeometry()
        : CylindricalGeometry(
        1.0f, 1.0f, 1.0f,
        32, 4, true, true
) {}

CylindricalGeometry::CylindricalGeometry(
        float radiusTop, float radiusBottom, float height,
        int radialSegments, int heightSegments,
        bool closedTop, bool closedBottom
) : SurfaceGeometry(
        0.0f, 2.0f * M_PI, radialSegments,
        0.0f, 1.0f, heightSegments
), m_radiusTop{radiusTop}, m_radiusBottom{radiusBottom}, m_height{height} {

    calculateSurface();

    auto PI = static_cast<float>(M_PI);
    if (closedTop) {
        std::shared_ptr<Geometry> topGeometry = std::make_shared<PolygonGeometry>(radialSegments, radiusTop);

        glm::mat4x4 transform = glm::translate(glm::vec3(0.0f, height / 2.0f, 0.0f));
        transform *= glm::rotate(-PI / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        transform *= glm::rotate(-PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        topGeometry->applyMatrix(transform);
        merge(topGeometry);
    }

    if (closedBottom) {
        std::shared_ptr<Geometry> bottomGeometry = std::make_shared<PolygonGeometry>(radialSegments, radiusBottom);
        glm::mat4x4 transform = glm::translate(glm::vec3(0.0f, -height / 2.0f, 0.0f));
        transform *= glm::rotate(-PI / 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        transform *= glm::rotate(PI / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

        bottomGeometry->applyMatrix(transform);
        merge(bottomGeometry);
    }

//    if (closedBottom)
//    {
//        Geometry bottomGeometry = new PolygonGeometry(radialSegments, radiusBottom);
//        Matrix transform = Matrix.makeTranslation(0, -height/2, 0);
//        transform.rightMultiply( Matrix.makeRotationY(-Math.PI/2) );
//        transform.rightMultiply( Matrix.makeRotationX( Math.PI/2) );
//        bottomGeometry.applyMatrix( transform );
//        this.merge( bottomGeometry );
//    }
}

glm::vec3 CylindricalGeometry::surface(float u, float v) {
    return glm::vec3{
            (v * m_radiusTop + (1 - v) * m_radiusBottom) * std::sin(u),
            m_height * (v - 0.5f),
            (v * m_radiusTop + (1 - v) * m_radiusBottom) * std::cos(u),
    };
}
