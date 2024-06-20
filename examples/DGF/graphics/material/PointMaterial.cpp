#include "PointMaterial.h"

PointMaterial::PointMaterial() : BasicMaterial() {
    m_drawStyle = GL_POINTS;
    addRenderSetting(std::make_shared<RenderSettingPointSize>(16));
    // addRenderSetting(std::make_shared<RenderSettingRoundedPoints>(true));
}
