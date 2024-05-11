#ifndef INCLUDED_MN_RUN_H
#define INCLUDED_MN_RUN_H

#include "Window.h"
#include "Input.h"
#include <glad/glad.h>

namespace Mn {
    template<typename T>
    int Run(int width, int height, const std::string &title) {
        Window wnd(width, height, title);
        T scene;

        scene.initialize(wnd.width(), wnd.height());
        while (!wnd.should_close() && !scene.end()) {
            Window::update_input();
            scene.update(Window::input());
            scene.draw();

            wnd.prepare_for_next_frame();
        }

        return 0;
    }

//    template<typename T>
//    void Run(T &scene, Window &window) {
//        GLFWwindow *w = window.create();
//
//        scene.initialize(window.width(), window.height());
//
//        double previous_time, curr_time, frameDuration;
//        frameDuration = 1.0 / 60.0;
//        previous_time = glfwGetTime(); // time in seconds
//        double elapsed_time = 0;
//
//        while (!glfwWindowShouldClose(w)) {
//            curr_time = glfwGetTime();
//            double delta_time = curr_time - previous_time;
//            elapsed_time += delta_time;
//            previous_time = curr_time;
//
//            if (elapsed_time > frameDuration) {
//                while (elapsed_time > frameDuration) {
//                    elapsed_time -= frameDuration;
//                    Window::updateInput();
//                    scene.update(Window::input(), frameDuration);
//                }
//                scene.draw();
//                glfwSwapBuffers(w);
//            }
//
//            glfwPollEvents();
//        }
//        scene.cleanup();
//
//        window.destroy();
//    }

}

#endif //INCLUDED_MN_RUN_H
