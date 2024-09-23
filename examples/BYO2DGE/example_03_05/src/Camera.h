#ifndef BYO2DGE_CAMERA_H
#define BYO2DGE_CAMERA_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/*
 * Encapsulates the user define WC and Viewport functionality
 */

//enum class eViewport {
//    eOrgX = 0,
//    eOrgY = 1,
//    eWidth = 2,
//    eHeight = 3
//};

class Camera {
public:
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
    Camera();

    Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray);

//    void Create(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray);

    void setWCCenter(float xPos, float yPos);

    [[nodiscard]] glm::vec2 getWCCenter() const;

    void setWCWidth(float width);

    [[nodiscard]] float getWCWidth() const;

    [[nodiscard]] float getWCHeight() const;

    void setViewport(glm::ivec4 viewportArray);

    [[nodiscard]] glm::ivec4 getViewport() const;

    void setBackgroundColor(glm::vec4 newColor);

    [[nodiscard]] glm::vec4 getBackgroundColor() const;

    // Call before you start drawing with this camera
    void setViewAndCameraMatrix();

    // Getter for the View-Projection transform operator
    [[nodiscard]] glm::mat4 getCameraMatrix() const;

    void clear() const;

private:
    glm::vec2 mWCCenter{};
    float mWCWidth{};
    glm::ivec4 mViewport{};  // [x, y, width, height]

    // Camera transform operator
    glm::mat4 mCameraMatrix{};

    // background color
    glm::vec4 mBGColor{}; // RGB and Alpha
};


#endif //BYO2DGE_CAMERA_H
