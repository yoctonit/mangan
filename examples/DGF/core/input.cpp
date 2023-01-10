//
// Created by ivan on 26.9.2021..
//

#include "input.h"

bool Input::_quit = false;

//has the user quit the application? quit = false
bool Input::quit() {
    return _quit;
}

void Input::update() {

}

void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) _quit = true;
}
