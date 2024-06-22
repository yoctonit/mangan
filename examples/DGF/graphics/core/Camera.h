#ifndef DGF_GRAPHICS_CORE_CAMERA_H
#define DGF_GRAPHICS_CORE_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera();

    // angleOfView in RADIANS!!!
    Camera(float angleOfView, float aspectRatio, float near, float far);

    [[nodiscard]] glm::mat4 viewMatrix() const;

    [[nodiscard]] glm::mat4 projectionMatrix() const;

    void updateViewMatrix();

    void setPosition(glm::vec3 position);

protected:
    glm::vec3 m_position{};
    glm::vec3 m_center{};
    glm::vec3 m_up{};

    glm::mat4 m_viewMatrix{};
    glm::mat4 m_projectionMatrix{};

    bool m_shouldUpdate{};
};

#endif //DGF_GRAPHICS_CORE_CAMERA_H
