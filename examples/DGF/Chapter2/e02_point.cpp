#include "core/run.h"
#include "core/shader.h"

class Point {
public:
    Point() : shader_program_id(0) {}

    ~Point() {}

    void initialize(int width, int height) {
        shader_program_id = Mn::Shader::CreateFromFiles("shader/point.vert", "shader/point.frag");

        // Vertex array initialization
        GLuint vertex_array_id;
        glGenVertexArrays(1, &vertex_array_id);
        glBindVertexArray(vertex_array_id);

        glPointSize(10);
//        glViewport(0, 0, width, height);
    }

    void draw() const {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program_id);
        glDrawArrays(GL_POINTS, 0, 1);
    }

    void cleanup() {
        glUseProgram(0);
    }

private:
    GLuint shader_program_id;
};

int main() {
    Mn::Window window(800, 800, "Point");
    Point scene;
    Mn::RunStatic<Point>(scene, window);
    return 0;
}
