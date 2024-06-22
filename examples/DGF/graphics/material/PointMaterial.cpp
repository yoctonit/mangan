#include "PointMaterial.h"

PointMaterial::PointMaterial() : BasicMaterial() {
    m_drawStyle = GL_POINTS;
    m_renderSettings.Activate(RenderSettings::Type::PointSize);
    m_renderSettings.set(RenderSettings::Type::PointSize, 16.0f);
}
