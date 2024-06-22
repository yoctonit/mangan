#include "LineMaterial.h"

LineMaterial::LineMaterial() : BasicMaterial() {
    m_drawStyle = GL_LINES;
    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}

LineMaterial::LineMaterial(LineStyle lineStyle) : BasicMaterial() {
    if (lineStyle == LineStyle::Segments) {
        m_drawStyle = GL_LINES;
    } else if (lineStyle == LineStyle::Connected) {
        m_drawStyle = GL_LINE_STRIP;
    } else if (lineStyle == LineStyle::Loop) {
        m_drawStyle = GL_LINE_LOOP;
    }
    m_renderSettings.Activate(RenderSettings::Type::LineWidth);
}
