#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"


Camera::Camera() {
    m_position = glm::vec3(0.0f, 0.0f, 1.0f);
    m_center = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_viewMatrix = glm::lookAt(m_position, m_center, m_up);
    m_projectionMatrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 1000.0f);

    m_shouldUpdate = false;
}

Camera::Camera(float angleOfView, float aspectRatio, float near, float far) {
    m_position = glm::vec3(0.0f, 0.0f, 1.0f);
    m_center = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    m_viewMatrix = glm::lookAt(m_position, m_center, m_up);
    m_projectionMatrix = glm::perspective(angleOfView, aspectRatio, near, far);

    m_shouldUpdate = false;
}

glm::mat4 Camera::viewMatrix() const {
    return m_viewMatrix;
}

glm::mat4 Camera::projectionMatrix() const {
    return m_projectionMatrix;
}

void Camera::updateViewMatrix() {
    if (m_shouldUpdate) {
        m_viewMatrix = glm::lookAt(m_position, m_center, m_up);
    }
}

glm::vec3 Camera::getPosition() const {
    return m_position;
}

void Camera::setPosition(glm::vec3 position) {
    m_position = position;
    m_shouldUpdate = true;
}
