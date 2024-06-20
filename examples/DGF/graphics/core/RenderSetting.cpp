#include <glad/glad.h>
#include "RenderSetting.h"


RenderSettingPointSize::RenderSettingPointSize(int pointSize) : m_pointSize{pointSize} {}

void RenderSettingPointSize::apply() {
    glPointSize(m_pointSize);
}

/*
RenderSettingRoundedPoints::RenderSettingRoundedPoints(bool roundedPoints) : m_roundedPoints{roundedPoints}{}

void RenderSettingRoundedPoints::apply() {
    if ( m_roundedPoints )
        glEnable(GL_POINT_SMOOTH);
    else
        glDisable(GL_POINT_SMOOTH);
}
*/


RenderSettingLineWidth::RenderSettingLineWidth(int lineWidth) : m_lineWidth{lineWidth} {}

void RenderSettingLineWidth::apply() {
    glLineWidth(m_lineWidth);
}


RenderSettingDoubleSide::RenderSettingDoubleSide(bool doubleSide) : m_doubleSide{doubleSide} {}

void RenderSettingDoubleSide::apply() {
    if (m_doubleSide)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
}


RenderSettingWireframe::RenderSettingWireframe(bool wireframe) : m_wireframe{wireframe} {}

void RenderSettingWireframe::apply() {
    if (m_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
