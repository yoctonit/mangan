#ifndef INCLUDED_MN_WINDOW_H
#define INCLUDED_MN_WINDOW_H

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <string>
#include "Input.h"

namespace Mn {

    class Window {

    public:
        Window(int width, int height, std::string title);

        ~Window();

        static void update_input();

        [[nodiscard]] int width() const { return _width; }

        [[nodiscard]] int height() const { return _height; }

        [[nodiscard]] bool should_close() const { return glfwWindowShouldClose(_window); }

        void prepare_for_next_frame() const {
            glfwSwapBuffers(_window);
            glfwPollEvents();
        }

        [[nodiscard]] static const Input &input() { return _input; }

    private:
        static void _error_callback(int error, const char *description);

        static void _key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

        static void _mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

        static void _cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);

        GLFWwindow *_window;
        int _width;
        int _height;
        int _gl_major;
        int _gl_minor;
        std::string _title;
        static Input _input;
    };

}

#endif //INCLUDED_MN_WINDOW_H
