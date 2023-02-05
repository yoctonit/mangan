#include "Run.h"
#include "VBO.h"
#include "Shader.h"

#include <vector>

class ExampleScene {
public:
    void initialize(int, int) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        std::vector<float> vertices = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };
        Mn::VBO buffer(vertices);
        buffer.activate();
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        Mn::Shader::Program program("shader/basic.vs", "shader/basic.fs");
        shader = program.id();
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glBindVertexArray(0);
    }

    void update(const Mn::Input &input, double delta_time) {
    }

    void cleanup() {}

private:
    unsigned int VAO;
    unsigned int shader{};
};

int main() {
    Mn::Window window(800, 600, "ExampleScene");
    ExampleScene scene;
    Mn::RunStatic<ExampleScene>(scene, window);
    return 0;
}
