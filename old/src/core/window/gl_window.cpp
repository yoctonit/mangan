//
// Created by ivan on 21.4.2020..
//
#include "gl_window.h"
#include <iostream>

namespace mn {

    gl_window::message_loop* gl_window::_message_loop_pointer = nullptr;

    gl_window& gl_window::instance() {
        static gl_window window_instance;
        return window_instance;
    }

    bool gl_window::create(int width, int height, const std::string &title,
            GLint gl_major, GLint gl_minor, unsigned int fps) {

        // glfwSetErrorCallback(error_callback);

        if (!glfwInit())
            return false;

        // Define version and compatibility settings
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (_window == nullptr) {
            glfwTerminate();
            return false;
        }

        glfwSetKeyCallback(_window, key_callback);

        glfwMakeContextCurrent(_window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            glfwTerminate();
            return false;
        }
        glfwSwapInterval(1);

        int w, h;
        glfwGetFramebufferSize(_window, &w, &h);

        _width = w;
        _height = h;

        _message_loop.set_fps(fps);
        _message_loop.set_screen_dimensions(_width, _height);

        _message_loop_pointer = &_message_loop;

        return true;
    }

    void gl_window::clean_up() {
        _window = nullptr;
        glfwTerminate();
    }

    // Is called whenever a key is pressed/released via GLFW
    void gl_window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        if (_message_loop_pointer == nullptr) return;

        if (action == GLFW_PRESS) {
            _message_loop_pointer->get_input()->_on_key_down(key);
        }
        if (action == GLFW_RELEASE) {
            _message_loop_pointer->get_input()->_on_key_up(key);
        }

        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void gl_window::message_loop::run(GLFWwindow *window) {
        if (_scene != nullptr) _scene->initialize();
        else if (_setup != nullptr) _setup();

        double frame_duration = 1.0 / double(_fps);  // in seconds

        // glfwGetTime returns time in seconds
        double start_time = glfwGetTime();
        double elapsed_time = 0;

        while(!glfwWindowShouldClose(window)) {
            double curr_time = glfwGetTime();
            double delta_time = curr_time - start_time;

            start_time = curr_time;
            elapsed_time += delta_time;

            if (elapsed_time > frame_duration) {
                while (elapsed_time > frame_duration) {
                    elapsed_time -= frame_duration;

                    _input._update();

                    if (_scene != nullptr) {
                        _scene->update(frame_duration, _input);
                    } else if (_update != nullptr)
                        _update(frame_duration, _input);
                }

                if (_scene != nullptr) {
                    _scene->clear();
                    _scene->draw();
                } else if (_draw != nullptr) {
                    _draw();
                }

                glfwSwapBuffers(window);
            }

            glfwPollEvents();
        }

        glfwDestroyWindow(window);

        glfwTerminate();
    }

    void gl_window::message_loop::run_test(GLFWwindow *window) {
        if (_scene != nullptr) _scene->initialize();
        else if (_setup != nullptr) _setup();

        double frame_duration = 1.0 / double(_fps);  // in seconds

        while(!glfwWindowShouldClose(window)) {
            _input._update();

            if (_input.is_clicked(mn::key::s)) {
                // std::cout << "update\n";

                if (_scene != nullptr) {
                    _scene->update(frame_duration, _input);
                } else if (_update != nullptr) {
                    _update(frame_duration, _input);
                }
            }

            if (_input.is_clicked(mn::key::d)) {
                // std::cout << "draw and swap buffers\n";

                if (_scene != nullptr) {
                    _scene->clear();
                    _scene->draw();
                } else if (_draw != nullptr) {
                    _draw();
                }

                glfwSwapBuffers(window);
            }

            glfwPollEvents();
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

}
