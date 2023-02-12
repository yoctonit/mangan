//
// Created by Ivan on 01-Feb-23.
//

#ifndef OPENGL_EXAMPLES_CAMERA_H
#define OPENGL_EXAMPLES_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray) : mCameraMatrix{1.0f} {
        mWCCenter = wcCenter;
        mWCWidth = wcWidth;
        mViewport = viewportArray;  // [x, y, width, height]

        // Camera transform operator
        mCameraMatrix = glm::mat4{1.0f};

        // background color
        mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
    }

    // #region Basic getter and setters

    void setWCCenter(float xPos, float yPos) {
        mWCCenter.x = xPos;
        mWCCenter.y = yPos;
    }

    glm::vec2 getWCCenter() { return mWCCenter; }

    void setWCWidth(float width) { mWCWidth = width; }

    [[nodiscard]] float getWCWidth() const { return mWCWidth; }

    float getWCHeight() {
        // viewportH/viewportW
//        float ratio = mViewport[(int)eViewport::eHeight] / mViewport[(int)eViewport::eWidth];
        float ratio = (float) mViewport[3] / (float) mViewport[2];
        return getWCWidth() * ratio;
    }

    void setViewport(glm::vec4 viewportArray) { mViewport = viewportArray; }

    glm::vec4 getViewport() { return mViewport; }

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
        glScissor(mViewport[0], // x position of bottom-left corner of the area to be drawn
                  mViewport[1], // y position of bottom-left corner of the area to be drawn
                  mViewport[2], // width of the area to be drawn
                  mViewport[3]);// height of the area to be drawn

        // Step A3: set the color to be clear
        glClearColor(mBGColor[0], mBGColor[1], mBGColor[2], mBGColor[3]);  // set the color to be cleared
        // Step A4: enable the scissor area, clear, and then disable the scissor area
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);

        // Step B: Compute the Camera Matrix
        glm::vec2 center = getWCCenter();

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
private:
    glm::vec2 mWCCenter{};
    float mWCWidth{};
    glm::ivec4 mViewport{};  // [x, y, width, height]

    // Camera transform operator
    glm::mat4 mCameraMatrix;

    // background color
    glm::vec4 mBGColor{}; // RGB and Alpha
};


#endif //OPENGL_EXAMPLES_CAMERA_H
