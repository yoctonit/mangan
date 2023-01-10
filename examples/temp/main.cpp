#include "core/run.h"
#include "core/shader.h"
#include "core/buffer/gpu_buffer.h"
#include <iostream>

class Triangle {
public:
    Triangle() :
            shader_program_id(0), /* vertex_pos_location(0), vertex_col_location(0), */ buffer() {
        std::cout << "Triangle() " << (long long) this << "\n";
    }

    ~Triangle() { std::cout << "~Triangle() " << (long long) this << "\n"; }

    void initialize(int width, int height) {
        std::cout << "initialize triangle\n";

        shader_program_id = Mn::Shader::CreateFromFiles("shader/basic.vert", "shader/basic.frag");

        // Vertex array initialization
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        // first 3 element specify coordinates, and next 3 color of one vertex
        const std::vector<float> vertices{
                -0.5f, -0.22867f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.22867f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.57735f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        buffer.create(vertices, GL_ARRAY_BUFFER);
        buffer.activate();

        GLuint vertex_pos_location = Mn::Shader::Location(shader_program_id, "a_position");
        glEnableVertexAttribArray(vertex_pos_location);
        glVertexAttribPointer(vertex_pos_location, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(GLfloat), nullptr);

        GLuint vertex_col_location = Mn::Shader::Location(shader_program_id, "a_color");
        glEnableVertexAttribArray(vertex_col_location);
        glVertexAttribPointer(vertex_col_location, 3, GL_FLOAT, GL_FALSE,
                              6 * sizeof(GLfloat), (void *) (sizeof(float) * 3));
        glViewport(0, 0, width, height);
    }

    void draw() const {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    void cleanup() {
        std::cout << "cleanup triangle\n";
        glUseProgram(0);
    }

private:
    GLuint shader_program_id;
//    GLuint vertex_pos_location;
//    GLuint vertex_col_location;
    mn::gpu_buffer buffer;
};

int main() {
    Mn::Window window(800, 800, "Triangle");
    Triangle scene;
    Mn::RunStatic<Triangle>(scene, window);
    return 0;
}
