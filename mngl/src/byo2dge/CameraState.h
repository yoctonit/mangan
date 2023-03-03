//
// Created by Ivan on 28-Feb-23.
//

#ifndef OPENGL_EXAMPLES_CAMERA_STATE_H
#define OPENGL_EXAMPLES_CAMERA_STATE_H

#include "Lerp.h"

class CameraState {
private:
    int kCycles;  // number of cycles to complete the transition
    float kRate;  // rate of change for each cycle
    LerpVec2 mCenter;
    Lerp mWidth;

public:
    //
    CameraState(glm::vec2 center, float width)
    : kCycles{300}, kRate{0.1f}, mCenter{center, kCycles, kRate},
      mWidth{width, kCycles, kRate} {
    }

    glm::vec2 getCenter() { return mCenter.get(); }
    float getWidth() { return mWidth.get(); }

    void setCenter(glm::vec2 c) { mCenter.setFinal(c); }
    void setWidth(float w) { mWidth.setFinal(w); }

    void update() {
        mCenter.update();
        mWidth.update();
    }

    void config(float stiffness, int duration) {
        mCenter.config(stiffness, duration);
        mWidth.config(stiffness, duration);
    }
};


#endif //OPENGL_EXAMPLES_CAMERA_STATE_H
