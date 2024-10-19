#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "BoundingBox.h"

Camera::Camera() = default;

Camera::Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray) {
    mWCCenter = wcCenter;
    mWCWidth = wcWidth;
    mViewport = viewportArray;  // [x, y, width, height]

    // Camera transform operator
    mCameraMatrix = glm::mat4{1.0f};

    // background color
    mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
}

//void Camera::Create(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray) {
//    mWCCenter = wcCenter;
//    mWCWidth = wcWidth;
//    mViewport = viewportArray;  // [x, y, width, height]
//
//    // Camera transform operator
//    mCameraMatrix = glm::mat4{1.0f};
//
//    // background color
//    mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
//}

void Camera::setWCCenter(float xPos, float yPos) {
    mWCCenter.x = xPos;
    mWCCenter.y = yPos;
}

glm::vec2 Camera::getWCCenter() const {
    return mWCCenter;
}

void Camera::setWCWidth(float width) {
    mWCWidth = width;
}

[[nodiscard]] float Camera::getWCWidth() const {
    return mWCWidth;
}

float Camera::getWCHeight() const {
    // viewportH/viewportW
    // float ratio = mViewport[(int)eViewport::eHeight] / mViewport[(int)eViewport::eWidth];
    float ratio = (float) mViewport[3] / (float) mViewport[2];
    return getWCWidth() * ratio;
}

void Camera::setViewport(glm::ivec4 viewportArray) {
    mViewport = viewportArray;
}

glm::ivec4 Camera::getViewport() const {
    return mViewport;
}

void Camera::setBackgroundColor(glm::vec4 newColor) {
    mBGColor = newColor;
}

glm::vec4 Camera::getBackgroundColor() const {
    return mBGColor;
}

// call before you start drawing with this camera
void Camera::setViewAndCameraMatrix() {
    // Compute the Camera Matrix
    glm::vec2 center = getWCCenter();

    // Following the translation, scale to: (-1, -1) to (1, 1): a 2x2 square at origin
    mCameraMatrix = glm::scale(glm::mat4{1.0f}, glm::vec3(2.0f / getWCWidth(), 2.0f / getWCHeight(), 1.0f));

    // First operation to perform is to translate camera center to the origin
    mCameraMatrix = glm::translate(mCameraMatrix, glm::vec3(-center.x, -center.y, 0.0f));
}

// Getter for the View-Projection transform operator
[[nodiscard]] glm::mat4 Camera::getCameraMatrix() const {
    return mCameraMatrix;
}

void Camera::clear() const {
    // Set up the viewport: area on canvas to be drawn
    glViewport(mViewport[0],     // x position of bottom-left corner of the area to be drawn
               mViewport[1],     // y position of bottom-left corner of the area to be drawn
               mViewport[2],  // width of the area to be drawn
               mViewport[3]  // height of the area to be drawn
    );
    // Set up the scissor area to limit the clear area
    glScissor(mViewport[0],     // x position of bottom-left corner of the area to be drawn
              mViewport[1],     // y position of bottom-left corner of the area to be drawn
              mViewport[2],  // width of the area to be drawn
              mViewport[3]  // height of the area to be drawn
    );
    // set the color to be cleared
    glClearColor(mBGColor[0], mBGColor[1], mBGColor[2], mBGColor[3]);
    // Enable the scissor area, clear, and then disable the scissor area
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}

unsigned int Camera::collideWCBound(const Transform &aXform, float zone) const {
    BoundingBox bbox(aXform.getPosition(), aXform.getWidth(), aXform.getHeight());
    float w = zone * getWCWidth();
    float h = zone * getWCHeight();
    BoundingBox cameraBound(getWCCenter(), w, h);
    return cameraBound.boundCollideStatus(bbox);
}
