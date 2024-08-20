#include <glad/glad.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Window.h"


namespace Mn {

    Input Window::input_{};

    Window::Window() : width_{800}, height_{600}, title_{"Example"} {
        std::cout << "Window::Window()\n";
        Create();
    }

    Window::Window(int width, int height, std::string title)
            : width_{width}, height_{height}, title_{std::move(title)} {
        std::cout << "Window::Window(" << width_ << ", " << height_ << ", " << title_ << ")\n";
        Create();
    }

    Window::~Window() {
        std::cout << "Window::~Window()\n";

        glfwDestroyWindow(window_);
        TerminateGlfw();
    }

    void Window::SetTitle(const std::string &title) {
        title_ = title;
    }

    void Window::SetDimensions(int width, int height) {
        width_ = width;
        height_ = height;
    }

    Input &Window::GetInput() {
        return input_;
    }

    void Window::Create() {
        std::cout << "Window::Create(" << title_ << ", " << width_ << ", " << height_ << ")\n";

        InitializeGlfw();
        CreateGlfwWindow();
        SetupCallbacks();
        LoadOpenGlExtensions();

        input_.SetWindowSize_(width_, height_);
    }

    void Window::Close() {
        glfwSetWindowShouldClose(window_, GL_TRUE);
    }

    void Window::Display() const {
        glfwSwapBuffers(window_);
    }

    void Window::CaptureCursor() const {
        // tell GLFW to capture our mouse
        glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool Window::IsOpen() const {
        auto shouldClose = static_cast<bool>(glfwWindowShouldClose(window_));
        return !shouldClose;
    }

    int Window::Width() const {
        return width_;
    }

    int Window::Height() const {
        return height_;
    }

    void Window::OnGlfwError(int error_code, const char *error_message) {
        std::cerr << "Error (" << error_code << "): " << error_message << std::endl;
    }

    void Window::InitializeGlfw() {
        std::cout << "GLFW: Initialize library.\n";

        glfwSetErrorCallback(Window::OnGlfwError);

        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("GLFW: Initialization failed.");
        }
    }

    void Window::TerminateGlfw() {
        std::cout << "GLFW: Terminate library.\n";
        glfwTerminate();
    }

    void Window::CreateGlfwWindow() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
        if (window_ == nullptr) {
            TerminateGlfw();
            throw std::runtime_error("GLFW: Create window failed.");
        }
    }

    void Window::SetupCallbacks() {
        glfwSetKeyCallback(window_, KeyCallback);
        glfwSetMouseButtonCallback(window_, MouseCallback);
        glfwSetCursorPosCallback(window_, MousePositionCallback);
        glfwSetScrollCallback(window_, MouseScrollCallback);
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

    void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
        if (action == GLFW_PRESS) {
            input_.OnKeyDown_(key);
        } else if (action == GLFW_RELEASE) {
            input_.OnKeyUp_(key);
        }
        // if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        //    glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void Window::MouseCallback(GLFWwindow *window, int button, int action, int mods) {
        if (action == GLFW_PRESS)
            input_.OnMouseDown_(button);
        if (action == GLFW_RELEASE)
            input_.OnMouseUp_(button);
    }

    void Window::MousePositionCallback(GLFWwindow *window, double x_pos, double y_pos) {
        input_.OnMouseMove_((float) x_pos, (float) y_pos);
    }

    void Window::MouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset) {
        input_.OnMouseScroll_((float) x_offset, (float) y_offset);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

}
