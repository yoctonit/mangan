#include "Window.h"
#include <glad/glad.h>
#include <string>
#include <iostream>

namespace Mn {

    Input Window::_input;

    Window::Window(int width, int height, std::string title) :
            _window(nullptr),
            _width(width), _height(height),
            _gl_major(4), _gl_minor(3),
            _title(std::move(title)) {
        std::cout << "Window::Window(" << _width << ", " << _height << ", " << _title << ")\n";
        glfwSetErrorCallback(Window::_error_callback);

        if (!glfwInit())
            throw std::runtime_error("GLFW Initialization Failed");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _gl_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For APPLE?

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_window == nullptr)
            throw std::runtime_error("GLFW Create Window Failed");

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            throw std::runtime_error("Glad Loading Failed");

        glfwSwapInterval(1);
        glfwGetFramebufferSize(_window, &_width, &_height);

        glfwSetKeyCallback(_window, Window::_key_callback);
        glfwSetMouseButtonCallback(_window, _mouse_button_callback);
        glfwSetCursorPosCallback(_window, _cursor_position_callback);
    }

    Window::~Window() {
        std::cout << "\nWindow::~Window()\n";
        std::cout << "=================\n";
        if (_window != nullptr) {
            std::cout << "Destroying window\n";
            glfwDestroyWindow(_window);
            _window = nullptr;
        }
        std::cout << "Terminate glfw library\n";
        glfwTerminate();
    }

    void Window::update_input() { _input._update(); }

    void Window::_error_callback(int error, const char *description) {
        std::cerr << "Error: " << description << "\n";
    }

    void Window::_key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
        if (action == GLFW_PRESS) {
            _input._on_key_down(key);
        } else if (action == GLFW_RELEASE) {
            _input._on_key_up(key);
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void Window::_mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        if (action == GLFW_PRESS)
            _input._on_mouse_down(button);
        if (action == GLFW_RELEASE)
            _input._on_mouse_up(button);
    }

    void Window::_cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos) {
        _input._on_mouse_move((float) x_pos, (float) y_pos);
    }

}
