#include <glad/glad.h>
#include <iostream>
#include "RenderSettings.h"


namespace Mn {

    void RenderSettings::Apply() const {
        ApplyPointSize();
        ApplyLineWidth();
        ApplyDoubleSide();
        ApplyWireframe();
    }

    void RenderSettings::Set(Type type, bool value) {
        switch (type) {
            case Type::DoubleSide:
                mDoubleSide = value;
                break;
            case Type::Wireframe:
                mWireframe = value;
                break;
            default:
                std::cerr << "RenderSettings::Activate(Type type, bool value) called with unsupported type\n";
        }
    }

    void RenderSettings::Set(Type type, float value) {
        switch (type) {
            case Type::PointSize:
                mPointSize = value;
                break;
            case Type::LineWidth:
                mLineWidth = value;
                break;
            default:
                std::cerr << "RenderSettings::set(Type type, float value) called with unsupported type\n";
        }
    }

//    float RenderSettings::Value(Type type) const {
//        switch (type) {
//            case Type::PointSize:
//                return mPointSize;
//            case Type::LineWidth:
//                return mLineWidth;
//            case Type::DoubleSide:
//                return mDoubleSide ? 1.0f : 0.0f;
//            case Type::Wireframe:
//                return mWireframe ? 1.0f : 0.0f;
//        }
//        return 0.0f;
//    }

    void RenderSettings::ApplyPointSize() const {
        glPointSize(mPointSize);
    }

    void RenderSettings::ApplyLineWidth() const {
        glLineWidth(mLineWidth);
    }

    void RenderSettings::ApplyDoubleSide() const {
        if (mDoubleSide)
            glDisable(GL_CULL_FACE);
        else
            glEnable(GL_CULL_FACE);
    }

    void RenderSettings::ApplyWireframe() const {
        if (mWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

//    void RenderSettings::applyRoundedPoints() const {
//        if (!mActiveRoundedPoints) return;
//        if (m_roundedPoints)
//            glEnable(GL_POINT_SMOOTH);
//        else
//            glDisable(GL_POINT_SMOOTH);
//    }

}
