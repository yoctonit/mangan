#include "GridHelper.h"
#include "GridGeometry.h"
#include "../material/LineMaterial.h"


GridHelper::GridHelper() :
        GridHelper(
                10.0f, 10.0f,
                glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3(0.8f, 0.8f, 0.8f),
                1.0f
        ) {}

GridHelper::GridHelper(
        float size, int divisions,
        glm::vec3 gridColor, glm::vec3 centerColor,
        float lineWidth
) :
        Mesh(
                "grid",
                std::make_shared<GridGeometry>(size, divisions, gridColor, centerColor),
                std::make_shared<LineMaterial>()
        ) {
    m_material->uniforms()["useVertexColors"].data().m_dataBool = true;
    m_material->renderSettings().set(RenderSettings::Type::LineWidth, lineWidth);
}
