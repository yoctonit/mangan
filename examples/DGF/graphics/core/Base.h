#ifndef DGF_GRAPHICS_CORE_BASE_H
#define DGF_GRAPHICS_CORE_BASE_H

#include <string>
#include "Input.h"

class GLFWwindow;

class Base {
public:
    Base();

    virtual void initialize() = 0;

    virtual void update() = 0;

    void run();

    void run(int windowWidth, int windowHeight, const std::string &windowTitle);

protected:
    int m_windowWidth{};
    int m_windowHeight{};
    std::string m_windowTitle{};

    GLFWwindow *m_windowHandle{};

    bool m_running{};
    static Input m_input;

    double m_timeSeconds{};      // number of seconds application has been running
    double m_deltaTimeSeconds{}; // seconds since last iteration of run loop

    double m_previousTimeSeconds{};
    double m_currentTimeSeconds{};

private:
    void startup();

    void shutdown();

    static void OnGlfwError(int error_code, const char *error_message);

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

    static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

    static void MousePositionCallback(GLFWwindow *window, double x_pos, double y_pos);

};

#endif //DGF_GRAPHICS_CORE_BASE_H
