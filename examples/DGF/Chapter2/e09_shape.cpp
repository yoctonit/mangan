#include "core/run.h"
#include "core/input.h"
#include "core/shader.h"
#include "core/attribute.h"
#include "core/uniform.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

// render six points in a hexagon arrangement
class Shape {
public:
    Shape() : programRef(0), speed(0.5f) {}

    ~Shape() = default;

    void initialize(int width, int height) {
        programRef = Mn::Shader::CreateFromFiles(
                "shader/shape_translation.vert",
                "shader/shape_translation.frag"
        );

        glClearColor(0.0, 0.0, 0.0, 1.0);

        // set up vertex array object
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        // set up vertex attributes
        const std::vector<GLfloat> positionData{
                0.0f, 0.2f, 0.0f,
                0.2f, -0.2f, 0.0f,
                -0.2f, -0.2f, 0.0f
        };
        vertexCount = static_cast<GLsizei>(positionData.size()) / 3;

        Mn::Attribute positionAttribute(Mn::Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(programRef, "position");

        // set up uniforms
        translation = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{-0.5, 0.0, 0.0});
        translation.locateVariable(programRef, "translation");

        baseColor = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{1.0, 0.0, 0.0});
        baseColor.locateVariable(programRef, "baseColor");
    }

    void update(const Mn::Input &input, double delta_time) {
        float distance = speed * (float)delta_time;

        if (input.is_pressed(Mn::key::left))
            translation.Vector()[0] -= distance;
        if (input.is_pressed(Mn::key::right))
            translation.Vector()[0] += distance;
        if (input.is_pressed(Mn::key::down))
            translation.Vector()[1] -= distance;
        if (input.is_pressed(Mn::key::up))
            translation.Vector()[1] += distance;
    }

    void draw() const {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programRef);
        translation.uploadData();
        baseColor.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    static void cleanup() {
        glUseProgram(0);
    }

private:
    GLuint programRef{};
    GLuint vaoRef{};
    GLsizei vertexCount{};
    Mn::Uniform translation{};
    Mn::Uniform baseColor{};
    float speed;
};

int main() {
    try {
        Mn::Window window(800, 800, "Shape");
        Shape scene;
        Mn::Run<Shape>(scene, window);
        return 0;
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << '\n';
        return 1;
    }
}
