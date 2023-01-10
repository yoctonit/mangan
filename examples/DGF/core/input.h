//
// Created by ivan on 26.9.2021..
//

#ifndef GLFRAMEWORK_INPUT_H
#define GLFRAMEWORK_INPUT_H

#include <GLFW/glfw3.h>

class Input {
public:
    Input() = default;

    static bool quit();

    static void update();

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

private:
    static bool _quit;
};

#endif //GLFRAMEWORK_INPUT_H
