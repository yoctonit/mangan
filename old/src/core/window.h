//
// Created by ivan on 23.12.2022.
//
#ifndef INCLUDED_MN_WINDOW_H
#define INCLUDED_MN_WINDOW_H

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include "input.h"

namespace Mn {

    class Window {

    public:
        Window(int width, int height, std::string title);

        ~Window();

        [[nodiscard]] int width() const { return _width; }

        [[nodiscard]] int height() const { return _height; }

        [[nodiscard]] static const Input& input() { return _input; }

        GLFWwindow *create();
        static void updateInput() { _input._update(); };

        void destroy();

    private:
        static void _error_callback(int error, const char *description);
        static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        static void _cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

        GLFWwindow *_window;
        std::string _title;
        int _width;
        int _height;
        int _gl_major;
        int _gl_minor;
        static Input _input;
    };

}

#endif //INCLUDED_MN_WINDOW_H
