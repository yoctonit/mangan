#include "PointLightHelper.h"

#include <utility>
#include "../geometry/SphereGeometry.h"
#include "../material/SurfaceMaterial.h"

PointLightHelper::PointLightHelper(const std::shared_ptr<PointLight> &light, float size, float lineWidth)
        : Mesh("point-light-helper",
               std::make_shared<SphereGeometry>(size, 4, 2),
               std::make_shared<SurfaceMaterial>()
) {
    m_material->uniforms()["baseColor"].data().m_dataVec3 = light->color();

    m_material->renderSettings().Activate(RenderSettings::Type::DoubleSide);
    m_material->renderSettings().set(RenderSettings::Type::DoubleSide, true);

    m_material->renderSettings().Activate(RenderSettings::Type::Wireframe);
    m_material->renderSettings().set(RenderSettings::Type::Wireframe, true);

    m_material->renderSettings().Activate(RenderSettings::Type::LineWidth);
    m_material->renderSettings().set(RenderSettings::Type::LineWidth, lineWidth);
};

PointLightHelper::PointLightHelper(const std::shared_ptr<PointLight> &light)
        : PointLightHelper(light, 0.1f, 1.0f) {}
