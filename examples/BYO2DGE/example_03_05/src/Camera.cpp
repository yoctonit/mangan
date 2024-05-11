#include "Camera.h"

Camera::Camera() = default;

Camera::Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray) : mCameraMatrix{1.0f} {
    mWCCenter = wcCenter;
    mWCWidth = wcWidth;
    mViewport = viewportArray;  // [x, y, width, height]

    // Camera transform operator
    mCameraMatrix = glm::mat4{1.0f};

    // background color
    mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
}

void Camera::Create(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray) {
    mCameraMatrix = glm::identity<glm::mat4>();
    mWCCenter = wcCenter;
    mWCWidth = wcWidth;
    mViewport = viewportArray;  // [x, y, width, height]

    // Camera transform operator
    mCameraMatrix = glm::mat4{1.0f};

    // background color
    mBGColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f); // RGB and Alpha
}

void Camera::WCCenter(float xPos, float yPos) {
    mWCCenter.x = xPos;
    mWCCenter.y = yPos;
}

glm::vec2 Camera::WCCenter() const {
    return mWCCenter;
}

void Camera::WCWidth(float width) {
    mWCWidth = width;
}

[[nodiscard]] float Camera::WCWidth() const {
    return mWCWidth;
}

float Camera::WCHeight() const {
    // viewportH/viewportW
    // float ratio = mViewport[(int)eViewport::eHeight] / mViewport[(int)eViewport::eWidth];
    float ratio = (float) mViewport[3] / (float) mViewport[2];
    return WCWidth() * ratio;
}

void Camera::Viewport(glm::vec4 viewportArray) {
    mViewport = viewportArray;
}

glm::vec4 Camera::Viewport() const {
    return mViewport;
}

void Camera::BackgroundColor(glm::vec4 newColor) {
    mBGColor = newColor;
}

glm::vec4 Camera::BackgroundColor() const {
    return mBGColor;
}

// call before you start drawing with this camera
void Camera::SetViewAndCameraMatrix() {
    // Compute the Camera Matrix
    glm::vec2 center = WCCenter();

    // Following the translation, scale to: (-1, -1) to (1, 1): a 2x2 square at origin
    mCameraMatrix = glm::scale(glm::mat4{1.0f}, glm::vec3(2.0f / WCWidth(), 2.0f / WCHeight(), 1.0f));

    // First operation to perform is to translate camera center to the origin
    mCameraMatrix = glm::translate(mCameraMatrix, glm::vec3(-center.x, -center.y, 0.0f));
}

// Getter for the View-Projection transform operator
[[nodiscard]] glm::mat4 Camera::CameraMatrix() const {
    return mCameraMatrix;
}

void Camera::Clear() const {
    // Set up the viewport: area on canvas to be drawn
    glViewport(mViewport[0],  // x position of bottom-left corner of the area to be drawn
               mViewport[1],  // y position of bottom-left corner of the area to be drawn
               mViewport[2],  // width of the area to be drawn
               mViewport[3]); // height of the area to be drawn
    // Set up the scissor area to limit the clear area
    glScissor(mViewport[0], // x position of bottom-left corner of the area to be drawn
              mViewport[1], // y position of bottom-left corner of the area to be drawn
              mViewport[2], // width of the area to be drawn
              mViewport[3]);// height of the area to be drawn
    // Set the color to be clear
    glClearColor(mBGColor[0], mBGColor[1], mBGColor[2], mBGColor[3]);  // set the color to be cleared
    // Enable the scissor area, clear, and then disable the scissor area
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}
