#include "core/run.h"
#include "core/shader.h"
#include "core/attribute.h"
#include <stdexcept>
#include <iostream>

// render six points in a hexagon arrangement
class Shape {
public:
    Shape() : shader_program_id(0) {}

    ~Shape() = default;

    void initialize(int width, int height) {
        shader_program_id = Mn::Shader::CreateFromFiles("shader/shape.vert", "shader/shape.frag");

        // Vertex array initialization
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        // render settings (optional)
        glLineWidth(4);

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
        Mn::Attribute positionAttribute(Mn::Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(shader_program_id, "position");
    }

    void draw() const {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program_id);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    }

    static void cleanup() {
        glUseProgram(0);
    }

private:
    GLuint shader_program_id{};
    GLsizei vertexCount{};
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
