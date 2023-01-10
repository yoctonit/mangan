//
// Created by ivan on 27.9.2021..
//
#include <stdexcept>
#include <iostream>
#include "../core/base.h"
#include "../core/openGLUtils.h"
#include "../core/attribute.h"

// render two shapes
class Test : public Base {
public:
    Test() : Base() {}

    void initialize() override {
        // vertex shader code
        std::string vsCode = R"(
        #version 460 core
        in vec3 position;
        in vec3 vertexColor;
        out vec3 color;
        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
            color = vertexColor;
        }
        )";

        // fragment shader code
        std::string fsCode = R"(
        #version 460 core
        in vec3 color;
        out vec4 fragColor;
        void main() {
            fragColor = vec4(color.r, color.g, color.b, 1.0);
        }
        )";

        // initialize program
        // send code to GPU and compile; store program reference
        programRef = OpenGLUtils::initializeProgram(vsCode, fsCode);

        // render settings (optional)
        glPointSize(10);
        glLineWidth(4);

        // set up vertex array object
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        // set up vertex attributes
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

        const std::vector<GLfloat> colorData{
            1.0f, 0.0f, 0.0f,
            1.0f, 0.5f, 0.0f,
            1.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.5f, 0.0f, 1.0f
        };
        Attribute colorAttribute(Attribute::Type::Vec3, colorData);
        colorAttribute.associateVariable(programRef, "vertexColor");
    }

    void update() override {
        glUseProgram(programRef);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    }

private:
    GLuint programRef{};
    GLuint vaoRef{};
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
