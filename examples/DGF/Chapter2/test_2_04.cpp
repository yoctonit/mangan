#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"


class Test_2_04 : public Base {
public:
    void initialize() override {
        // load code, send to GPU, and compile; store program reference
        m_programRef = Shader::FromFiles("shader/Test_2_03.vert", "shader/Test_2_03.frag").id();

        // render settings (optional)

        // set line width
        glLineWidth(4);

        // set up vertex array object: triangle
        glGenVertexArrays(1, &m_vaoTriRef);
        glBindVertexArray(m_vaoTriRef);

        const std::vector<GLfloat> positionDataTri{
                -0.5f, 0.8f, 0.0f,
                -0.2f, 0.2f, 0.0f,
                -0.8f, 0.2f, 0.0f
        };
        Attribute positionAttributeTri(Attribute::Type::Vec3, positionDataTri);
        positionAttributeTri.associateVariable(m_programRef, "position");

        // set up vertex array object: square
        glGenVertexArrays(1, &m_vaoSquareRef);
        glBindVertexArray(m_vaoSquareRef);

        const std::vector<GLfloat> positionDataSquare{
                0.8f, 0.8f, 0.0f,
                0.8f, 0.2f, 0.0f,
                0.2f, 0.2f, 0.0f,
                0.2f, 0.8f, 0.0f
        };
        Attribute positionAttributeSquare(Attribute::Type::Vec3, positionDataSquare);
        positionAttributeSquare.associateVariable(m_programRef, "position");
    }

    void update() override {
        // select program to use when rendering
        glUseProgram(m_programRef);

        // draw the triangle
        glBindVertexArray(m_vaoTriRef);
        glDrawArrays(GL_LINE_LOOP, 0, 3);

        // draw the square
        glBindVertexArray(m_vaoSquareRef);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

private:
    GLuint m_programRef{};
    GLuint m_vaoTriRef{};
    GLuint m_vaoSquareRef{};
};

int main() {
    Test_2_04().run();
    return 0;
}
