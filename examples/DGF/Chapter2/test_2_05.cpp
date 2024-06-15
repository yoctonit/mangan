#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"


class Test_2_05 : public Base {
public:
    void initialize() override {
        // load code, send to GPU, and compile; store program reference
        m_programRef = Shader::FromFiles("shader/Test_2_05.vert", "shader/Test_2_05.frag").id();

        // render settings (optional)

        // set line width
        glPointSize(10);
        glLineWidth(4);

        // set up vertex array object
        glGenVertexArrays(1, &m_vaoRef);
        glBindVertexArray(m_vaoRef);

        const std::vector<GLfloat> positionData{
                0.8f, 0.0f, 0.0f,
                0.4f, 0.6f, 0.0f,
                -0.4f, 0.6f, 0.0f,
                -0.8f, 0.0f, 0.0f,
                -0.4f, -0.6f, 0.0f,
                0.4f, -0.6f, 0.0f
        };
        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(m_programRef, "position");

        const std::vector<GLfloat> colorData{
                1.0f, 0.0f, 0.0f,
                1.0f, 0.5f, 0.0f,
                1.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f,
                0.5f, 0.0f, 1.0f
        };
        Attribute colorAttribute(Attribute::Type::Vec3, colorData);
        colorAttribute.associateVariable(m_programRef, "vertexColor");
    }

    void update() override {
        glUseProgram(m_programRef);

        // draw the object
        glBindVertexArray(m_vaoRef);
        // glDrawArrays(GL_POINTS, 0, 6);
        glDrawArrays(GL_LINE_LOOP, 0, 6);
        // glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    }

private:
    GLuint m_programRef{};
    GLuint m_vaoRef{};
};

int main() {
    Test_2_05().run();
    return 0;
}
