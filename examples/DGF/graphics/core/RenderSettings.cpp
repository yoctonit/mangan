#include <glad/glad.h>
#include <iostream>
#include "RenderSettings.h"


void RenderSettings::apply() {
    applyPointSize();
    applyLineWidth();
    applyDoubleSide();
    applyWireframe();
    // applyRoundedPoints();
}

bool RenderSettings::isActive(Type type) const {
    switch (type) {
        case Type::PointSize:
            return m_activePointSize;
        case Type::LineWidth:
            return m_activeLineWidth;
        case Type::DoubleSide:
            return m_activeDoubleSide;
        case Type::Wireframe:
            return m_activeWireframe;
    }
    return false;
}

void RenderSettings::Activate(Type type) {
    switch (type) {
        case Type::PointSize:
            m_activePointSize = true;
            break;
        case Type::LineWidth:
            m_activeLineWidth = true;
            break;
        case Type::DoubleSide:
            m_activeDoubleSide = true;
            break;
        case Type::Wireframe:
            m_activeWireframe = true;
            break;
    }
}

void RenderSettings::Deactivate(Type type) {
    switch (type) {
        case Type::PointSize:
            m_activePointSize = false;
            break;
        case Type::LineWidth:
            m_activeLineWidth = false;
            break;
        case Type::DoubleSide:
            m_activeDoubleSide = false;
            break;
        case Type::Wireframe:
            m_activeWireframe = false;
            break;
    }
}

void RenderSettings::set(Type type, float value) {
    switch (type) {
        case Type::PointSize:
            m_pointSize = value;
            break;
        case Type::LineWidth:
            m_lineWidth = value;
            break;
        default:
            std::cerr << "RenderSettings::set(Type type, int value) called with unsupported type\n";
    }
}

void RenderSettings::set(Type type, bool value) {
    switch (type) {
        case Type::DoubleSide:
            m_doubleSide = value;
            break;
        case Type::Wireframe:
            m_wireframe = value;
            break;
        default:
            std::cerr << "RenderSettings::set(Type type, bool value) called with unsupported type\n";
    }
}

// for boolean settings (doubleSide and wireframe) returns 0 or 1
float RenderSettings::getValue(Type type) const {
    switch (type) {
        case Type::PointSize:
            return m_pointSize;
        case Type::LineWidth:
            return m_lineWidth;
        case Type::DoubleSide:
            return m_doubleSide ? 1.0f : 0.0f;
        case Type::Wireframe:
            return m_wireframe ? 1.0f : 0.0f;
    }
    return 0.0f;
}

void RenderSettings::applyPointSize() const {
    if (!m_activePointSize) return;
    glPointSize(m_pointSize);
}

void RenderSettings::applyLineWidth() const {
    if (!m_activeLineWidth) return;
    glLineWidth(m_lineWidth);
}

void RenderSettings::applyDoubleSide() const {
    if (!m_activeDoubleSide) return;
    if (m_doubleSide)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
}

void RenderSettings::applyWireframe() const {
    if (!m_activeWireframe) return;
    if (m_wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/*
void RenderSettings::applyRoundedPoints() const {
    if (!m_activeRoundedPoints) return;
    if ( m_roundedPoints )
        glEnable(GL_POINT_SMOOTH);
    else
        glDisable(GL_POINT_SMOOTH);
}
*/
