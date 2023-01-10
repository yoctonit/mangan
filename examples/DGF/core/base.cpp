//
// Created by ivan on 15.9.2021..
//
#include <iostream>
#include "base.h"

Base::Base(int width, int height, const std::string &title)
        : _width{width}, _height{height}, _running{false},
          _frameDuration{1.0 / 60.0}, _time{0.0} {
    // glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    _glfwConfigure();
    _window = _glfwCreateWindow(width, height, title);
    _glfwSetupWindow(_window);

    // glfwGetFramebufferSize(_window, &_width, &_height);
    // std::cout << _width << ',' << _height << '\n';
}

void Base::_glfwConfigure() {
    // define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // initialize buffers to perform antialiasing
    // pygame.display.gl_set_attribute(pygame.GL_MULTISAMPLEBUFFERS, 1)
    // pygame.display.gl_set_attribute( pygame.GL_MULTISAMPLESAMPLES, 4)
}

GLFWwindow *Base::_glfwCreateWindow(int width, int height, const std::string &title) {
    GLFWwindow *wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (wnd == nullptr) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    return wnd;
}

void Base::_glfwSetupWindow(GLFWwindow *wnd) {
    glfwSetKeyCallback(wnd, Input::key_callback);

    glfwMakeContextCurrent(wnd);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);
}

void Base::initialize() {}

void Base::update() {}

void Base::run() {
    _startup();

    _mainLoop();

    _shutdown(_window, EXIT_SUCCESS);
}

void Base::_startup() {
    try {
        initialize();
        _running = true;
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << '\n';
        _shutdown(_window, EXIT_FAILURE);
    }
}

void Base::_mainLoop() {
    double start_time = glfwGetTime(); // time in seconds
    double elapsed_time = 0;

    while (!glfwWindowShouldClose(_window) && _running) {
        double curr_time = glfwGetTime();
        double delta_time = curr_time - start_time;

        start_time = curr_time;
        elapsed_time += delta_time;
        _time += delta_time;

        if (elapsed_time > _frameDuration) {
            while (elapsed_time > _frameDuration) {
                elapsed_time -= _frameDuration;
                _processInput();
                update();
            }

            // render
            // display image on screen
            glfwSwapBuffers(_window);
        }

        glfwPollEvents();
    }
}

void Base::_processInput() {
    Input::update();
    if (Input::quit()) {
        _running = false;
    }
}

void Base::_shutdown(GLFWwindow *wnd, int exitCode) {
    glfwDestroyWindow(wnd);
    glfwTerminate();
    exit(exitCode);
}

// Is called whenever a key is pressed/released via GLFW
//void Base::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (_message_loop_pointer == nullptr) return;
//
//    if (action == GLFW_PRESS) {
//        _message_loop_pointer->get_input()->_on_key_down(key);
//    }
//    if (action == GLFW_RELEASE) {
//        _message_loop_pointer->get_input()->_on_key_up(key);
//    }
//
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//}
