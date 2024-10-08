#ifndef JOEY_LIB_CAMERA_H
#define JOEY_LIB_CAMERA_H

#include <glm/glm.hpp>


// Default camera values
inline const float YAW = -90.0f;
inline const float PITCH = 0.0f;
inline const float SPEED = 2.5f;
inline const float SENSITIVITY = 0.1f;
inline const float ZOOM = 45.0f;


// An abstract camera class that processes input
// and calculates the corresponding Euler Angles,
// Vectors and Matrices for use in OpenGL
class Camera {
public:
    // Defines several possible options for camera movement.
    // Used as abstraction to stay away from window-system specific input methods.
    enum class Movement {
        Forward, Backward, Left, Right
    };

    // camera Attributes
    glm::vec3 Position{};
    glm::vec3 Front{};
    glm::vec3 Up{};
    glm::vec3 Right{};
    glm::vec3 WorldUp{};

    // euler Angles
    float Yaw{};
    float Pitch{};

    // camera options
    float MovementSpeed{};
    float MouseSensitivity{};
    float Zoom{};

    // constructor with vectors
    explicit Camera(
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = YAW,
            float pitch = PITCH
    );

    // constructor with scalar values
    Camera(
            float posX, float posY, float posZ,
            float upX, float upY, float upZ,
            float yaw, float pitch
    );

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    [[nodiscard]] glm::mat4 GetViewMatrix() const;

    // processes input received from any keyboard-like input system.
    // Accepts input parameter in the form of camera defined ENUM
    // (to abstract it from windowing systems)
    void ProcessKeyboard(Movement direction, float deltaTime);

    // processes input received from a mouse input system.
    // Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float x_offset, float y_offset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event.
    // Only requires input data on the vertical wheel-axis
    void ProcessMouseScroll(float y_offset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

};

#endif //JOEY_LIB_CAMERA_H
