#include "core/run.h"
#include "core/shader.h"
#include "core/attribute.h"
#include "core/uniform.h"
#include <stdexcept>
#include <iostream>

// render six points in a hexagon arrangement
class Shape {
public:
    Shape() : programRef(0) {}

    ~Shape() = default;

    void initialize(int width, int height) {
        programRef = Mn::Shader::CreateFromFiles(
                "shader/shape_translation.vert",
                "shader/shape_translation.frag"
        );

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
        translation1 = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{-0.5, 0.0, 0.0});
        translation1.locateVariable(programRef, "translation");

        translation2 = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{0.5, 0.0, 0.0});
        translation2.locateVariable(programRef, "translation");

        baseColor1 = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{1.0, 0.0, 0.0});
        baseColor1.locateVariable(programRef, "baseColor");

        baseColor2 = Mn::Uniform(Mn::Uniform::Type::Vec3, std::vector<GLfloat>{0.0, 0.0, 1.0});
        baseColor2.locateVariable(programRef, "baseColor");
    }

    void draw() const {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programRef);

        // draw the first triangle
        translation1.uploadData();
        baseColor1.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        // draw the second triangle
        translation2.uploadData();
        baseColor2.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    static void cleanup() {
        glUseProgram(0);
    }

private:
    GLuint programRef{};
    GLuint vaoRef{};
    GLsizei vertexCount{};
    Mn::Uniform translation1{};
    Mn::Uniform translation2{};
    Mn::Uniform baseColor1{};
    Mn::Uniform baseColor2{};
};

int main() {
    try {
        Mn::Window window(800, 800, "Shape");
        Shape scene;
        Mn::RunStatic<Shape>(scene, window);
        return 0;
    } catch (const std::runtime_error &e) {
        std::cout << e.what() << '\n';
        return 1;
    }
}
