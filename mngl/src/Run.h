//
// Created by ivan on 24.12.2022..
//

#ifndef INCLUDED_MN_MESSAGE_LOOP_H
#define INCLUDED_MN_MESSAGE_LOOP_H

#include "Window.h"
#include "Input.h"
#include <glad/glad.h>
#include <memory>
#include <iostream>
#include <utility>

namespace Mn {
    template<typename T>
    void RunStatic(T &scene, Window &window) {
        GLFWwindow *w = window.create();

        scene.initialize(window.width(), window.height());
        while (!glfwWindowShouldClose(w)) {
            scene.draw();

            glfwSwapBuffers(w);
            glfwWaitEvents();
        }
        scene.cleanup();

        window.destroy();
    }

    template<typename T>
    void Run(T &scene, Window &window) {
        GLFWwindow *w = window.create();

        scene.initialize(window.width(), window.height());

        double previous_time, curr_time, frameDuration;
        frameDuration = 1.0 / 60.0;
        previous_time = glfwGetTime(); // time in seconds
        curr_time = previous_time;
        double elapsed_time = 0;

        while (!glfwWindowShouldClose(w)) {
            curr_time = glfwGetTime();
            double delta_time = curr_time - previous_time;
            elapsed_time += delta_time;
            previous_time = curr_time;

            if (elapsed_time > frameDuration) {
                while (elapsed_time > frameDuration) {
                    elapsed_time -= frameDuration;
                    Window::updateInput();
                    scene.update(Window::input(), frameDuration);
                }
                scene.draw();

                glfwSwapBuffers(w);
            }

            glfwPollEvents();
        }
        scene.cleanup();

        window.destroy();
    }

}

#endif //INCLUDED_MN_MESSAGE_LOOP_H
