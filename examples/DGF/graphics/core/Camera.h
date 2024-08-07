#ifndef DGF_GRAPHICS_CORE_CAMERA_H
#define DGF_GRAPHICS_CORE_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera();

    // angleOfView in RADIANS!!!
    Camera(float angleOfView, float aspectRatio, float near, float far);

    void setPerspective(float angleOfView, float aspectRatio, float near, float far);

    void setPerspective();

    void setOrthographic(float left, float right,
                         float bottom, float top,
                         float near, float far);

    void setOrthographic();

    void setLookAt(glm::vec3 target);

    [[nodiscard]] glm::mat4 viewMatrix() const;

    [[nodiscard]] glm::mat4 projectionMatrix() const;

    void updateViewMatrix();

    [[nodiscard]] glm::vec3 getPosition() const;

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
