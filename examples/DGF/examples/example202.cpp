//
// Created by ivan on 26.9.2021..
//
#include <stdexcept>
#include <iostream>
#include "../core/base.h"
#include "../core/openGLUtils.h"

class Test : public Base {
public:
    Test() : programRef(0), Base() {}

    void initialize() override {
        // vertex shader code
        std::string vsCode = R"(
        #version 430 core
        void main(void) {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
        }
        )";

        // fragment shader code
        std::string fsCode = R"(
        #version 430 core
        out vec4 fragColor;
        void main() {
            fragColor = vec4(1.0, 1.0, 0.0, 1.0);
        }
        )";

        // initialize program

        // send code to GPU and compile; store program reference
        programRef = OpenGLUtils::initializeProgram(vsCode, fsCode);

        // set up vertex array object
        GLuint vaoRef;
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        // render settings (optional)

        // set point width and height
        glPointSize(10);

        OpenGLUtils::printSystemInfo();
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(programRef);

        // renders geometric objects using selected program
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    GLuint programRef;
};

int main() {
    Test scene;

    try {
        scene.run();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
}
