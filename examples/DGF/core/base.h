//
// Created by ivan on 15.9.2021..
//
#ifndef GLFRAMEWORK_BASE_H
#define GLFRAMEWORK_BASE_H

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <string>
#include "input.h"

class Base {
public:
    explicit Base(int width = 512, int height = 512, const std::string &title = "Simple example");

    virtual void initialize();

    virtual void update();

    virtual void run();

    // [[nodiscard]] double runningTime() const { return _time; }

protected:
    GLFWwindow *_window;
    int _width;
    int _height;

    bool _running;
    double _frameDuration; // seconds, make it configurable?
    double _time; // number of seconds application has been running

private:
    static void _glfwConfigure();

    static GLFWwindow *_glfwCreateWindow(int width, int height, const std::string &title);

    static void _glfwSetupWindow(GLFWwindow *wnd);

    void _startup();

    void _mainLoop();

    void _processInput();

    static void _shutdown(GLFWwindow *wnd, int exitCode);
};

#endif //GLFRAMEWORK_BASE_H
