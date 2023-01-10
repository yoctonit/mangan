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

        // render settings (optional)
        glLineWidth(4);

        // set up vertex array object - triangle
        glGenVertexArrays(1, &vaoTriRef);
        glBindVertexArray(vaoTriRef);
        const std::vector<GLfloat> positionDataTri{
                -0.5f, 0.8f, 0.0f,
                -0.2f, 0.2f, 0.0f,
                -0.8f, 0.2f, 0.0f
        };
        vertexCountTri = static_cast<GLsizei>(positionDataTri.size()) / 3;
        Attribute positionAttributeTri(Attribute::Type::Vec3, positionDataTri);
        positionAttributeTri.associateVariable(programRef, "position");

        // set up vertex array object - square
        glGenVertexArrays(1, &vaoSquareRef);
        glBindVertexArray(vaoSquareRef);
        const std::vector<GLfloat> positionDataSquare{
                0.8f, 0.8f, 0.0f,
                0.8f, 0.2f, 0.0f,
                0.2f, 0.2f, 0.0f,
                0.2f, 0.8f, 0.0f
        };
        vertexCountSquare = static_cast<GLsizei>(positionDataSquare.size()) / 3;
        Attribute positionAttributeSquare(Attribute::Type::Vec3, positionDataSquare);
        positionAttributeSquare.associateVariable(programRef, "position");
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(programRef);

        // draw the triangle
        glBindVertexArray(vaoTriRef);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCountTri);

        // draw the square
        glBindVertexArray(vaoSquareRef);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCountSquare);
    }

private:
    GLuint programRef{};
    GLuint vaoTriRef{};
    GLsizei vertexCountTri{};
    GLuint vaoSquareRef{};
    GLsizei vertexCountSquare{};
};

int main() {
    Test scene;

    try {
        scene.run();
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << '\n';
    }
}
