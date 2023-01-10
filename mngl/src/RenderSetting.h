//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_RENDERSETTING_H
#define OPENGL_EXAMPLES_RENDERSETTING_H

#include <string>
#include <iostream>
#include <utility>
#include <glad/glad.h>
#include "Object3D.h"

class RenderSetting {
public:
    std::string settingName;
    float fData{};
    bool lData{};

    RenderSetting() = default;

    RenderSetting(const std::string &settingName_, float f_, bool b_) {
        settingName = settingName_;
        fData = f_;
        lData = b_;
    }

    void apply() const {
        if (settingName == "pointSize") {
            glPointSize(fData);
//        } else if (settingName == "roundedPoints") {
//            if (lData)
//                glEnable(GL_POINT_SMOOTH);
//            else
//                glDisable(GL_POINT_SMOOTH);
        } else if (settingName == "lineWidth") {
            glLineWidth(fData);
        } else if (settingName == "doubleSide") {
            if (lData)
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
        } else if (settingName == "wireframe") {
            if (lData)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            std::cout << "Unknown render setting: " + settingName << "'n";
        }
    }
};

#endif //OPENGL_EXAMPLES_RENDERSETTING_H
