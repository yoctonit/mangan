#include "LineMaterial.h"

LineMaterial::LineMaterial() : BasicMaterial() {
    m_drawStyle = GL_LINES;
    addRenderSetting(std::make_shared<RenderSettingLineWidth>(1));
}

LineMaterial::LineMaterial(LineStyle lineStyle) {
    if (lineStyle == LineStyle::Segments) {
        m_drawStyle = GL_LINES;
    } else if (lineStyle == LineStyle::Connected) {
        m_drawStyle = GL_LINE_STRIP;
    } else if (lineStyle == LineStyle::Loop) {
        m_drawStyle = GL_LINE_LOOP;
    }

    addRenderSetting(std::make_shared<RenderSettingLineWidth>(1));
}
