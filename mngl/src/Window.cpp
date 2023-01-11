//
// Created by ivan on 23.12.2022.
//
#include "Window.h"
#include <glad/glad.h>

#include <string>
#include <iostream>
#include <utility>

namespace Mn {

    Input Window::_input;

    Window::Window(int width, int height, std::string title) :
            _window(nullptr), _title(std::move(title)),
            _width(width), _height(height),
            _gl_major(4), _gl_minor(3) {
        std::cout << "Window(" << _width << ", " << _height << ", " << _title << ")\n";
    }

    Window::~Window() {
        std::cout << "Window::~Window()\n";
    }

    void Window::_error_callback(int error, const char *description) {
        std::cerr << "Error: " << description << "\n";
    }

    // Is called whenever a key is pressed/released via GLFW
    void Window::_key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
        if (action == GLFW_PRESS) {
            _input._on_key_down(key);
        }
        if (action == GLFW_RELEASE) {
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

    void Window::_cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
        _input._on_mouse_move(xpos, ypos);
    }


    GLFWwindow *Window::create() {
        std::cout << "Creating Window\n";
        glfwSetErrorCallback(Window::_error_callback);

        if (!glfwInit())
            throw std::runtime_error("GLFW Initialization Failed");

        // Define openGL version and compatibility settings
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _gl_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//        For APPLE?
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_window == nullptr)
            throw std::runtime_error("GLFW Create Window Failed");

        glfwMakeContextCurrent(_window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            throw std::runtime_error("Glad Loading Failed");

        glfwSwapInterval(1);
        glfwGetFramebufferSize(_window, &_width, &_height);

        _input._set_screen_dimensions(_width, _height);
        glfwSetKeyCallback(_window, Window::_key_callback);
        glfwSetMouseButtonCallback(_window, _mouse_button_callback);
        glfwSetCursorPosCallback(_window, _cursor_position_callback);

        return _window;
    }

    void Window::destroy() {
        if (_window != nullptr) {
            std::cout << "Destroying window\n";
            glfwDestroyWindow(_window);
            _window = nullptr;
        }
        std::cout << "Terminate glfw library\n";
        glfwTerminate();
    }

}
