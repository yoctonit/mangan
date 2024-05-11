#include "window/Window.h"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


namespace Mn {

    unsigned Window::windows_count_ = 0;
    bool Window::glfw_initialized_ = false;
    Input Window::input_;

    void Window::OnGlfwError(int error_code, const char *error_message) {
        std::cerr << "Error (" << error_code << "): " << error_message << std::endl;
    }

    void Window::InitializeGlfw() {
        if (glfw_initialized_) {
            return;
        }
        std::cout << "GLFW: Initialize library.\n";
        glfwSetErrorCallback(Window::OnGlfwError);
        glfw_initialized_ = static_cast<bool>(glfwInit());

        if (!glfw_initialized_) {
            throw std::runtime_error("GLFW: Initialization failed.");
        }
    }

    void Window::TerminateGlfw() {
        if (windows_count_ == 0) {
            std::cout << "GLFW: Terminate library.\n";
            glfwTerminate();
            glfw_initialized_ = false;
        }
    }

    void Window::CreateWindowGlfw(const std::string &title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window_ = glfwCreateWindow(width_, height_, title.c_str(), nullptr, nullptr);
        if (window_ == nullptr) {
            TerminateGlfw();
            throw std::runtime_error("GLFW: Create window failed.");
        }
        ++windows_count_;
    }

    void Window::LoadOpenGlExtensions() {
        glfwMakeContextCurrent(window_);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            TerminateGlfw();
            throw std::runtime_error("Glad: Loading failed.");
        }

        glfwSwapInterval(1);
        glfwGetFramebufferSize(window_, &width_, &height_);
    }

    void Window::SetupCallbacks() {
        glfwSetKeyCallback(window_, Window::KeyCallback_);
        glfwSetMouseButtonCallback(window_, MouseCallback_);
        glfwSetCursorPosCallback(window_, MousePositionCallback_);
    }

    Window::Window(const std::string &title, int width, int height) : width_{width}, height_{height} {
        std::cout << "Window::Window(" << title << ", " << width << ", " << height << ")\n";
        InitializeGlfw();
        CreateWindowGlfw(title);
        LoadOpenGlExtensions();
        SetupCallbacks();
        input_.SetWindowSize_(width, height);
    }

    Window::~Window() {
        std::cout << "Window::~Window()\n";
        glfwDestroyWindow(window_);
        --windows_count_;
        TerminateGlfw();
    }

    int Window::Width() const {
        return width_;
    }

    int Window::Height() const {
        return height_;
    }

    bool Window::ShouldClose() const {
        return static_cast<bool>(glfwWindowShouldClose(window_));
    }

    void Window::PollEvents() {

        glfwPollEvents();
    }

    void Window::SwapBuffers() const {
        glfwSwapBuffers(window_);
    }

    void Window::KeyCallback_(GLFWwindow *window, int key, int scancode, int action, int mode) {
        if (action == GLFW_PRESS) {
            input_.OnKeyDown_(key);
        } else if (action == GLFW_RELEASE) {
            input_.OnKeyUp_(key);
        }
        // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        //    glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void Window::MouseCallback_(GLFWwindow *window, int button, int action, int mods) {
        if (action == GLFW_PRESS)
            input_.OnMouseDown_(button);
        if (action == GLFW_RELEASE)
            input_.OnMouseUp_(button);
    }

    void Window::MousePositionCallback_(GLFWwindow *window, double x_pos, double y_pos) {
        input_.OnMouseMove_((float) x_pos, (float) y_pos);
    }

}
