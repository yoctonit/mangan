#ifndef EXAMPLE4_CAMERA_H
#define EXAMPLE4_CAMERA_H

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
    Camera();

    Camera(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray);

    void Create(glm::vec2 wcCenter, float wcWidth, glm::ivec4 viewportArray);

    void WCCenter(float xPos, float yPos);

    [[nodiscard]] glm::vec2 WCCenter() const;

    void WCWidth(float width);

    [[nodiscard]] float WCWidth() const;

    [[nodiscard]] float WCHeight() const;

    void Viewport(glm::vec4 viewportArray);

    [[nodiscard]] glm::vec4 Viewport() const;

    void BackgroundColor(glm::vec4 newColor);

    [[nodiscard]] glm::vec4 BackgroundColor() const;

    // Call before you start drawing with this camera
    void SetViewAndCameraMatrix();

    // Getter for the View-Projection transform operator
    [[nodiscard]] glm::mat4 CameraMatrix() const;

    void Clear() const;

private:
    glm::vec2 mWCCenter{};
    float mWCWidth{};
    glm::ivec4 mViewport{};  // [x, y, width, height]

    // Camera transform operator
    glm::mat4 mCameraMatrix{};

    // background color
    glm::vec4 mBGColor{}; // RGB and Alpha
};


#endif //EXAMPLE4_CAMERA_H
