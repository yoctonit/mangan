//
// Created by ivan on 21.4.2020..
//

#ifndef INCLUDED_GL_WINDOW_H
#define INCLUDED_GL_WINDOW_H

// GLAD
#include <glad/glad.h>

// GLFW
// #define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <functional>
#include "input.h"
#include "scene.h"

namespace mn {

    class gl_window {

    public:
        static gl_window& instance();

        bool create(int width, int height, const std::string &title,
            GLint gl_major, GLint gl_minor, unsigned int fps = 60);
        void clean_up();

        void set_scene(scene* s) { _message_loop.set_scene(s); }
        void action() {
            if (_window != nullptr) _message_loop.run(_window);
        }
        void action_test() {
            if (_window != nullptr) _message_loop.run_test(_window);
        }

        void set_setup(std::function<void()> fn) { _message_loop.set_setup(fn); }
        void set_update(std::function<void(double, const input&)> fn) {
            _message_loop.set_update(fn);
        }
        void set_draw(std::function<void()> fn) { _message_loop.set_draw(fn); }

        [[nodiscard]] int width() const { return _width; }
        [[nodiscard]] int height() const { return _height; }

    private:
        gl_window() : _window(nullptr), _width(0), _height(0), _message_loop() {}
        ~gl_window() = default;
        gl_window(const gl_window&) = default;
        const gl_window& operator=(const gl_window& win) const {
            if (this == &win) return *this; // self-assignment check
            return *this; // return *this anyway, because it's a singleton
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

        class message_loop {
        public:
            explicit message_loop(unsigned int fps = 60) :
            _fps(fps), _scene(nullptr), _setup(nullptr),
            _update(nullptr), _draw(nullptr), _input() {}

            void run(GLFWwindow* window);
            void run_test(GLFWwindow* window);

            void set_fps(unsigned int fps) { _fps = fps; }
            void set_scene(scene* s) { _scene = s; }
            void set_setup(std::function<void()> fn) { _setup = fn; }
            void set_update(std::function<void(double, const input&)> fn) { _update = fn; }
            void set_draw(std::function<void()> fn) { _draw = fn; }
            void set_screen_dimensions(int screen_width, int screen_height) {
                _input._set_screen_dimensions(screen_width, screen_height);
            }
            input* get_input() { return &_input; }

        private:
            unsigned int _fps;

            scene* _scene;
            std::function<void()> _setup;
            std::function<void(double, const input&)> _update;
            std::function<void()> _draw;

            input _input;
        };

        GLFWwindow* _window;
        int _width;
        int _height;
        message_loop _message_loop;

        static message_loop* _message_loop_pointer;
    };

}

#endif //INCLUDED_GL_WINDOW_H
