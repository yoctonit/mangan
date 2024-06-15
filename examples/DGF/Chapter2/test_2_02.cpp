#include "core/Base.h"
#include "core/Shader.h"


class Test_2_02 : public Base {
public:
    void initialize() override {
        m_shader = Shader::FromFiles("shader/Test_2_02.vert", "shader/Test_2_02.frag");

        // Set up vertex array object
        GLuint vertexArrayId;
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        glPointSize(10);
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(m_shader.id());

        // render geometric objects using selected program
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    Shader m_shader{};
};


int main() {
    Test_2_02().run();
    return 0;
}
