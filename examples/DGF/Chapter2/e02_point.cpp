#include "engine/Run.h"
#include "graphics/Shader.h"


class PointScene {
public:
    PointScene() {
        m_shader = Mn::Shader::FromFiles("shader/Test_2_02.vert", "shader/Test_2_02.frag");

        // Set up vertex array object
        GLuint vertexArrayId;
        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        glPointSize(10);
    }

    void Render() const {
        // select program to use when rendering
        glUseProgram(m_shader.id());

        // render geometric objects using selected program
        glDrawArrays(GL_POINTS, 0, 1);
    }

private:
    Mn::Shader m_shader{};
};

int main() {
    Mn::Window wnd(1024, 1024, "Chapter-02 Example-02 Point Scene");
    Mn::ShowStaticScene<PointScene>(wnd);
    return 0;
}
