#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"


class Test_2_02 : public Base {
public:
    void initialize() override {
        // load code, send to GPU, and compile; store program reference
        m_shader = Shader::FromFiles("shader/Test_2_03.vert", "shader/Test_2_03.frag");

        // render settings (optional)

        // set line width
        glLineWidth(4);

        // set up vertex array object
        GLuint vaoRef;
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        const std::vector<GLfloat> positionData{
                0.8f, 0.0f, 0.0f,
                0.4f, 0.6f, 0.0f,
                -0.4f, 0.6f, 0.0f,
                -0.8f, 0.0f, 0.0f,
                -0.4f, -0.6f, 0.0f,
                0.4f, -0.6f, 0.0f
        };
        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(m_shader.id(), "position");
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(m_shader.id());

        // renders geometric objects using selected program
        glDrawArrays(GL_LINE_LOOP, 0, 6);
    }

private:
    Shader m_shader{};
};

int main() {
    Test_2_02().run();
    return 0;
}
