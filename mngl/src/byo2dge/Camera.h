//
// Created by Ivan on 01-Feb-23.
//

#ifndef OPENGL_EXAMPLES_CAMERA_H
#define OPENGL_EXAMPLES_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BoundingBox.h"
#include "CameraState.h"
#include "Oscilate.h"

class eViewport{
    static int eOrgX;
    static int eOrgY;
    static int eWidth;
    static int eHeight;
};
int eViewport::eOrgX = 0;
int eViewport::eOrgY = 1;
int eViewport::eWidth = 2;
int eViewport::eHeight=  3;

class CameraShake {
private:
    glm::vec2 mOrgCenter{};
    glm::vec2 mShakeCenter{};
    std::shared_ptr<ShakeVec2> mShake;

public:
    // state is the CameraState to be shaken
    CameraShake(const std::shared_ptr<CameraState>& state, glm::vec2 deltas, glm::vec2 freqs, int shakeDuration) {
        mOrgCenter = state->getCenter();
        mShakeCenter = mOrgCenter;
        mShake = std::make_shared<ShakeVec2>(deltas, freqs, shakeDuration);
    }

    void update() {
        glm::vec2 delta = mShake->getNext();
//        vec2.add(mShakeCenter, mOrgCenter, delta);
        mShakeCenter = mOrgCenter + delta;
    }

    bool done() {
        return mShake->done();
    }

    void reShake() {
        mShake->reStart();
    }

    glm::vec2 getCenter() { return mShakeCenter; }

    void setRefCenter(glm::vec2 c) {
        mOrgCenter[0] = c[0];
        mOrgCenter[1] = c[1];
    }
};

/*
 * Encapsulates the user define WC and Viewport functionality
 */
class Camera {
public:
    enum class eViewport {
        eOrgX = 0,
        eOrgY = 1,
        eWidth = 2,
        eHeight = 3
    };

    // wcCenter: is a vec2
    // wcWidth: is the width of the user defined WC
    //      Height of the user defined WC is implicitly defined by the viewport aspect ratio
    //      Please refer to the following
    // viewportRect: an array of 4 elements
    //      [0] [1]: (x,y) position of lower left corner on the canvas (in pixel)
    //      [2]: width of viewport
    //      [3]: height of viewport
    //
    //  wcHeight = wcWidth * viewport[3]/viewport[2]
    //
    Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray, int viewportBound = 0)
    : mCameraMatrix{1.0f} {
        mCameraState = std::make_shared<CameraState>(wcCenter, wcWidth);
//        mWCCenter = wcCenter;
//        mWCWidth = wcWidth;
        mViewport = viewportArray;  // [x, y, width, height]
        mViewportBound = viewportBound;
        setViewport(viewportArray, mViewportBound);

        // Camera transform operator
        mCameraMatrix = glm::mat4{1.0f};

        // background color
        mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
    }

    // #region Basic getter and setters

    void setWCCenter(float xPos, float yPos) {
//        mWCCenter.x = xPos;
//        mWCCenter.y = yPos;
        mCameraState->setCenter(glm::vec2(xPos, yPos));
    }

    glm::vec2 getWCCenter() { return mCameraState->getCenter(); }

    void setWCWidth(float width) { mCameraState->setWidth(width); }

    [[nodiscard]] float getWCWidth() const { return mCameraState->getWidth(); }

    float getWCHeight() {
        // viewportH/viewportW
//        float ratio = mViewport[(int)eViewport::eHeight] / mViewport[(int)eViewport::eWidth];
        float ratio = (float) mViewport[3] / (float) mViewport[2];
        return mCameraState->getWidth() * ratio;
    }

    void setViewport(glm::ivec4 viewportArray, int bound) {
        if (bound == 0) {
            bound = mViewportBound;
        }
//        mViewport = viewportArray;
        mViewport[0] = viewportArray[0] + bound;
        mViewport[1] = viewportArray[1] + bound;
        mViewport[2] = viewportArray[2] - ( 2 * bound);
        mViewport[3] = viewportArray[3] - (2 * bound);
        mScissorBound[0] = viewportArray[0];
        mScissorBound[1] = viewportArray[1];
        mScissorBound[2] = viewportArray[2];
        mScissorBound[3] = viewportArray[3];
    }

    glm::ivec4 getViewport() {
//        return mViewport;
        return mScissorBound;
    }

    void setBackgroundColor(glm::vec4 newColor) { mBGColor = newColor; }

    glm::vec4 getBackgroundColor() { return mBGColor; }
    // #endregion

    // #region Compute and access camera transform matrix

    // call before you start drawing with this camera
    void setViewAndCameraMatrix() {
        // Step A1: Set up the viewport: area on canvas to be drawn
        glViewport(mViewport[0],  // x position of bottom-left corner of the area to be drawn
                   mViewport[1],  // y position of bottom-left corner of the area to be drawn
                   mViewport[2],  // width of the area to be drawn
                   mViewport[3]); // height of the area to be drawn
        // Step A2: set up the scissor area to limit the clear area
        glScissor(mScissorBound[0], // x position of bottom-left corner of the area to be drawn
                  mScissorBound[1], // y position of bottom-left corner of the area to be drawn
                  mScissorBound[2], // width of the area to be drawn
                  mScissorBound[3]);// height of the area to be drawn

        // Step A3: set the color to be clear
        glClearColor(mBGColor[0], mBGColor[1], mBGColor[2], mBGColor[3]);  // set the color to be cleared
        // Step A4: enable the scissor area, clear, and then disable the scissor area
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // Step B: Compute the Camera Matrix
        // glm::vec2 center = getWCCenter();
        glm::vec2 center;
        if (mCameraShake != nullptr) {
            center = mCameraShake->getCenter();
        } else {
            center = getWCCenter();
        }

        // Step B1: following the translation, scale to: (-1, -1) to (1, 1): a 2x2 square at origin
        mCameraMatrix = glm::scale(glm::mat4{1.0f}, glm::vec3(2.0f / getWCWidth(), 2.0f / getWCHeight(), 1.0f));

        // Step B2: first operation to perform is to translate camera center to the origin
        mCameraMatrix = glm::translate(mCameraMatrix, glm::vec3(-center.x, -center.y, 0.0f));
    }

    // Getter for the View-Projection transform operator
    [[nodiscard]] glm::mat4 getCameraMatrix() const {
        return mCameraMatrix;
    }
    // #endregion

    void update() {
        if (mCameraShake != nullptr) {
            if (mCameraShake->done()) {
                mCameraShake = nullptr;
            } else {
                mCameraShake->setRefCenter(getWCCenter());
                mCameraShake->update();
            }
        }
        mCameraState->update();
    }

// For LERP function configuration
    void configLerp(float stiffness, int duration) {
        mCameraState->config(stiffness, duration);
    }

    // Define camera shake
    void shake(glm::vec2 deltas, glm::vec2 freqs, int duration) {
        mCameraShake = std::make_shared<CameraShake>(mCameraState, deltas, freqs, duration);
    }

// Restart the shake
    bool reShake() {
        bool success = (mCameraShake != nullptr);
        if (success)
            mCameraShake->reShake();
        return success;
    }

    unsigned collideWCBound(const std::shared_ptr<Transform> &aXform, float zone) {
        BoundingBox bbox(aXform->getPosition(), aXform->getWidth(), aXform->getHeight());
        float w = zone * getWCWidth();
        float h = zone * getWCHeight();
        BoundingBox cameraBound(getWCCenter(), w, h);
        return cameraBound.boundCollideStatus(bbox);
    }

    // prevents the xform from moving outside the WC boundary.
    // by clamping the aXfrom at the boundary of WC,
    unsigned clampAtBoundary(const std::shared_ptr<Transform> &aXform, float zone) {
        unsigned status = collideWCBound(aXform, zone);
        if (status != eBoundCollideStatus::eInside) {
            glm::vec2 pos = aXform->getPosition();
            if ((status & eBoundCollideStatus::eCollideTop) != 0) {
                pos[1] = (getWCCenter())[1] + (zone * getWCHeight() / 2) - (aXform->getHeight() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideBottom) != 0) {
                pos[1] = (getWCCenter())[1] - (zone * getWCHeight() / 2) + (aXform->getHeight() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideRight) != 0) {
                pos[0] = (getWCCenter())[0] + (zone * getWCWidth() / 2) - (aXform->getWidth() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideLeft) != 0) {
                pos[0] = (getWCCenter())[0] - (zone * getWCWidth() / 2) + (aXform->getWidth() / 2);
            }
        }
        return status;
    }

    // pan the camera to ensure aXform is within camera bounds
// this is complementary to the ClampAtBound: instead of clamping aXform, now, move the camera
    void panWith(const std::shared_ptr<Transform> &aXform, float zone) {
        unsigned status = collideWCBound(aXform, zone);
        if (status != eBoundCollideStatus::eInside) {
            glm::vec2 pos = aXform->getPosition();
            glm::vec2 newC = getWCCenter();
            if ((status & eBoundCollideStatus::eCollideTop) != 0) {
                newC[1] = pos[1] + (aXform->getHeight() / 2) - (zone * getWCHeight() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideBottom) != 0) {
                newC[1] = pos[1] - (aXform->getHeight() / 2) + (zone * getWCHeight() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideRight) != 0) {
                newC[0] = pos[0] + (aXform->getWidth() / 2) - (zone * getWCWidth() / 2);
            }
            if ((status & eBoundCollideStatus::eCollideLeft) != 0) {
                newC[0] = pos[0] - (aXform->getWidth() / 2) + (zone * getWCWidth() / 2);
            }
            mCameraState->setCenter(newC);
        }
    }

    void panBy(float dx, float dy) {
        glm::vec2 newC = getWCCenter();
        newC[0] += dx;
        newC[1] += dy;
        mCameraState->setCenter(newC);
    }

    void panTo(float cx, float cy) {
        setWCCenter(cx, cy);
    }

// zoom with respect to the center
// zoom > 1 ==> zooming out, see more of the world
// zoom < 1 ==> zooming in, see less of the world, more detailed
// zoom < 0 is ignored
    void zoomBy(float zoom) {
        if (zoom > 0) {
            setWCWidth(getWCWidth() * zoom);
        }
    }

// zoom towards (pX, pY) by zoom: 
// zoom > 1 ==> zooming out, see more of the world
// zoom < 1 ==> zooming in, see less of the world, more detailed
// zoom < 0 is ignored
    void zoomTowards(glm::vec2 pos, float zoom) {
        glm::vec2 delta;
        glm::vec2 newC;
//        vec2.sub(delta, pos, mWCCenter);
        delta = pos - getWCCenter();

//        vec2.scale(delta, delta, zoom - 1);
        delta *= zoom - 1;
        newC = getWCCenter() - delta;

//        vec2.sub(mWCCenter, mWCCenter, delta);
        // mWCCenter = mWCCenter - delta;
        zoomBy(zoom);
        mCameraState->setCenter(newC);
    }


    float _mouseDCX(const Mn::Input &input) {
        return (float)input.get_mouse_x_screen_position() - (float)mViewport[0]; // eViewport::eOrgX
//        return input.getMousePosX() - mViewport[eViewport.eOrgX];
    }

    float _mouseDCY(const Mn::Input &input) {
        return (float)input.get_mouse_y_screen_position() - (float)mViewport[1]; // eViewport.eOrgY
//        return input.getMousePosY() - mViewport[eViewport.eOrgY];
    }

    bool isMouseInViewport (const Mn::Input &input) {
        float dcX = _mouseDCX(input);
        float dcY = _mouseDCY(input);
        return ((dcX >= 0) && (dcX < (float)mViewport[2]) && // eViewport.eWidth
                (dcY >= 0) && (dcY < (float)mViewport[3])); // eViewport.eHeight
    }

    float mouseWCX (const Mn::Input &input) {
        float minWCX = getWCCenter()[0] - getWCWidth() / 2;
        return minWCX + (_mouseDCX(input) * (getWCWidth() / (float)mViewport[2])); // eViewport.eWidth
    }

    float mouseWCY (const Mn::Input &input) {
        float minWCY = getWCCenter()[1] - getWCHeight() / 2;
        return minWCY + (_mouseDCY(input) * (getWCHeight() / (float)mViewport[3])); // eViewport.eHeight
    }

private:
    std::shared_ptr<CameraState> mCameraState;
    std::shared_ptr<CameraShake> mCameraShake;
    glm::vec2 mWCCenter{};
//    float mWCWidth{};
    glm::ivec4 mViewport{};  // [x, y, width, height]
    int mViewportBound{};  // [x, y, width, height]
    glm::ivec4 mScissorBound{};  // [x, y, width, height]

    // Camera transform operator
    glm::mat4 mCameraMatrix;

    // background color
    glm::vec4 mBGColor{}; // RGB and Alpha
};


#endif //OPENGL_EXAMPLES_CAMERA_H
