#include "SurfaceMaterial.h"

SurfaceMaterial::SurfaceMaterial() : BasicMaterial() {
    m_drawStyle = GL_TRIANGLES;
    addRenderSetting(std::make_shared<RenderSettingDoubleSide>(true));
    addRenderSetting(std::make_shared<RenderSettingWireframe>(false));
    addRenderSetting(std::make_shared<RenderSettingLineWidth>(1));
}
