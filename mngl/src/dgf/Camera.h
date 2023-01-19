//
// Created by ivan on 7.1.2023..
//

#ifndef OPENGL_EXAMPLES_CAMERA_H
#define OPENGL_EXAMPLES_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Object3D.h"

class Camera : public Object3D {
public:
    glm::mat4 viewMatrix{};
    glm::mat4 projectionMatrix{};

    Camera() {
        viewMatrix = glm::mat4(1.0f);
        projectionMatrix = glm::perspective(60.0f, 1.0f, 0.1f, 1000.0f);
    }

    Camera(float angleOfView, float aspectRatio, float near, float far) {
        viewMatrix = glm::mat4(1.0f);
        projectionMatrix = glm::perspective(angleOfView, aspectRatio, near, far);
    }

    void updateViewMatrix() {
        viewMatrix = glm::inverse(getWorldMatrix());
    }

    void setPerspective(float angleOfView, float aspectRatio, float near, float far) {
        projectionMatrix = glm::perspective(angleOfView, aspectRatio, near, far);
//        projectionMatrix = Matrix.makePerspective(angleOfView, aspectRatio, near, far);
    }

//    void setPerspective(glm::mat4 m) {
//        projectionMatrix = m;
////        projectionMatrix = Matrix.makePerspective();
//    }

    void setOrthographic(float left, float right, float bottom, float top, float near, float far) {
        projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
//        projectionMatrix = Matrix.makeOrthographic(left, right,bottom, top, near, far);
    }

//    void setOrthographic(glm::mat4 m)
//    {
//        projectionMatrix = m;
////        projectionMatrix = Matrix.makeOrthographic();
//    }
};

#endif //OPENGL_EXAMPLES_CAMERA_H
