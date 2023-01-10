//
// Created by ivan on 26.9.2021..
//
#include <stdexcept>
#include <iostream>
#include "../core/base.h"
#include "../core/openGLUtils.h"
#include "../core/attribute.h"

// render six points in a hexagon arrangement
class Test : public Base {
public:
    Test() : Base() {}

    void initialize() override {
        // vertex shader code
        std::string vsCode = R"(
        #version 460 core
        in vec3 position;
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
        )";

        // fragment shader code
        std::string fsCode = R"(
        #version 460 core
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
        // glLineWidth(4);

        // set up vertex attribute
        const std::vector<GLfloat> positionData{
                0.8f, 0.0f, 0.0f,
                0.4f, 0.6f, 0.0f,
                -0.4f, 0.6f, 0.0f,
                -0.8f, 0.0f, 0.0f,
                -0.4f, -0.6f, 0.0f,
                0.4f, -0.6f, 0.0f
        };
        vertexCount = static_cast<GLsizei>(positionData.size()) / 3;
        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(programRef, "position");
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(programRef);

        // renders geometric objects using selected program
        glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    }

private:
    GLuint programRef{};
    GLsizei vertexCount{};
};

int main() {
    Test scene;

    try {
        scene.run();
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << '\n';
    }
}
