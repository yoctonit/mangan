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

//        // Vertex array initialization
//        GLuint vertex_array_id;
//        glGenVertexArrays(1, &vertex_array_id);
//        glBindVertexArray(vertex_array_id);

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
        Mn::Attribute positionAttributeTri(Mn::Attribute::Type::Vec3, positionDataTri);
        positionAttributeTri.associateVariable(shader_program_id, "position");

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
        Mn::Attribute positionAttributeSquare(Mn::Attribute::Type::Vec3, positionDataSquare);
        positionAttributeSquare.associateVariable(shader_program_id, "position");
        
        // set up vertex attribute
        const std::vector<GLfloat> positionData{
                0.8f, 0.0f, 0.0f,
                0.4f, 0.6f, 0.0f,
                -0.4f, 0.6f, 0.0f,
                -0.8f, 0.0f, 0.0f,
                -0.4f, -0.6f, 0.0f,
                0.4f, -0.6f, 0.0f
        };
    }

    void draw() const {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program_id);

        // draw the triangle
        glBindVertexArray(vaoTriRef);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCountTri);

        // draw the square
        glBindVertexArray(vaoSquareRef);
        glDrawArrays(GL_LINE_LOOP, 0, vertexCountSquare);
    }

    static void cleanup() {
        glUseProgram(0);
    }

private:
    GLuint shader_program_id{};
    GLuint vaoTriRef{};
    GLsizei vertexCountTri{};
    GLuint vaoSquareRef{};
    GLsizei vertexCountSquare{};
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
