#include <glad/glad.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>

#include "Base.h"

Input Base::m_input{};

Base::Base() = default;

void Base::run() {
    run(1024, 1024, "Graphics Window");
}

void Base::run(int windowWidth, int windowHeight, const std::string &windowTitle) {
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_windowTitle = windowTitle;

    startup();    // setup window, input and opengl

    initialize(); // application-specific startup code

    // main loop ----------------------
    while (m_running) {
        // process input ----------------------
        // poll for window events; activates callbacks in Input class methods
        glfwPollEvents();

        // recalculate time variables
        m_currentTimeSeconds = glfwGetTime();
        m_deltaTimeSeconds = (m_currentTimeSeconds - m_previousTimeSeconds);
        m_timeSeconds += m_deltaTimeSeconds;
        m_previousTimeSeconds = m_currentTimeSeconds;

        m_input.update();

        if (m_input.isPressedKey(MN_KEY_ESCAPE) || glfwWindowShouldClose(m_windowHandle)) {
            m_running = false;
        }

        // update ----------------------
        update();

        // render ----------------------
        glfwSwapBuffers(m_windowHandle);
    }

    shutdown();
}

void Base::startup() {
    try {
        std::cout << "Starting program\n";

        glfwSetErrorCallback(Base::OnGlfwError);

        // initialize GLFW
        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("Unable to initialize GLFW");
        }

        // create window and associated OpenGL context
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_windowHandle = glfwCreateWindow(
                m_windowWidth, m_windowHeight,
                m_windowTitle.c_str(), nullptr, nullptr);
        if (m_windowHandle == nullptr) {
            glfwTerminate();
            throw std::runtime_error("Failed to create the GLFW window");
        }

        glfwSetKeyCallback(m_windowHandle, KeyCallback);
        glfwSetMouseButtonCallback(m_windowHandle, MouseCallback);
        glfwSetCursorPosCallback(m_windowHandle, MousePositionCallback);

        m_running = true;
        m_input.SetWindowSize_(m_windowWidth, m_windowHeight);

        m_timeSeconds = 0.0;
        m_deltaTimeSeconds = 1.0 / 60.0;
        m_currentTimeSeconds = m_previousTimeSeconds = glfwGetTime();

        // make the OpenGL context current: all function calls will apply to this context instance
        glfwMakeContextCurrent(m_windowHandle);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error("Failed to load OpenGL bindings");
        }

        // specify number of screen updates to wait before swapping buffers (via glfwSwapBuffers)
        //   setting to 1 enables vertical sync - synchronizes application frame rate to display refresh rate
        //   and prevents visual "screen tearing" artifacts
        glfwSwapInterval(1);
        // glfwGetFramebufferSize(m_windowHandle, &m_windowWidth, &m_windowHeight);


        std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";

    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }
}

void Base::shutdown() {
    std::cout << "Shutting down program\n";
    glfwDestroyWindow(m_windowHandle);
    glfwTerminate();
    glfwSetErrorCallback(nullptr);
}

void Base::OnGlfwError(int error_code, const char *error_message) {
    std::cerr << "Error (" << error_code << "): " << error_message << std::endl;
}

void Base::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (action == GLFW_PRESS) {
        m_input.OnKeyDown_(key);
    } else if (action == GLFW_RELEASE) {
        m_input.OnKeyUp_(key);
    }
}

void Base::MouseCallback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS)
        m_input.OnMouseDown_(button);
    if (action == GLFW_RELEASE)
        m_input.OnMouseUp_(button);
}

void Base::MousePositionCallback(GLFWwindow *window, double x_pos, double y_pos) {
    m_input.OnMouseMove_((float) x_pos, (float) y_pos);
}
