#include "SurfaceMaterial.h"

SurfaceMaterial::SurfaceMaterial() : BasicMaterial() {
    m_drawStyle = GL_TRIANGLES;

    m_renderSettings.Activate(RenderSettings::Type::DoubleSide);
    m_renderSettings.set(RenderSettings::Type::DoubleSide, true);

    m_renderSettings.Activate(RenderSettings::Type::Wireframe);
    m_renderSettings.set(RenderSettings::Type::Wireframe, false);

    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}
