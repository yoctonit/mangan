#include "AxesHelper.h"
#include "AxesGeometry.h"
#include "../material/LineMaterial.h"


AxesHelper::AxesHelper(float axisLength, float lineWidth) :
        Mesh(
                "axes",
                std::make_shared<AxesGeometry>(axisLength),
                std::make_shared<LineMaterial>()
        ) {
    m_material->uniforms()["useVertexColors"].data().m_dataBool = true;
    m_material->renderSettings().set(RenderSettings::Type::LineWidth, lineWidth);
}
