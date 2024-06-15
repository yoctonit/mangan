#include <cmath>
#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"
#include "core/Uniform.h"

typedef UniformVec3<std::vector<float>> UVec3;

class Test_2_09 : public Base {
public:
    void initialize() override {
        // load code, send to GPU, and compile; store program reference
        m_programRef = Shader::FromFiles("shader/Test_2_06.vert", "shader/Test_2_06.frag").id();

        // specify color used when clearing the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // set up vertex array object
        glGenVertexArrays(1, &m_vaoRef);
        glBindVertexArray(m_vaoRef);

        const std::vector<GLfloat> positionData{
                0.0f, 0.2f, 0.0f,
                0.2f, -0.2f, 0.0f,
                -0.2f, -0.2f, 0.0f
        };
        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(m_programRef, "position");

        // set up uniforms
        m_translationUniformRef = Uniform::locate(m_programRef, "translation");
        m_baseColorUniformRef = Uniform::locate(m_programRef, "baseColor");

        m_translation = UVec3(std::vector<float>{-0.5f, 0.0f, 0.0f});
        m_baseColor = UVec3(std::vector<float>{1.0f, 0.0f, 0.0f});
    }

    void update() override {
        // update data

        // change colors
        m_baseColor.data()[0] = (float) ((std::sin(3 * m_timeSeconds) + 1.0) / 2.0);

        // m_baseColor.data()[0] = (float) ((std::sin(m_timeSeconds) + 1.0) / 2.0);
        // m_baseColor.data()[1] = (float) ((std::sin(m_timeSeconds + 2.1) + 1.0) / 2.0);
        // m_baseColor.data()[2] = (float) ((std::sin(m_timeSeconds + 4.2) + 1.0) / 2.0);

        // render scene

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_programRef);
        glBindVertexArray(m_vaoRef);

        // draw the triangle
        m_translation.upload(m_translationUniformRef);
        m_baseColor.upload(m_baseColorUniformRef);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLuint m_programRef{};
    GLuint m_vaoRef{};

    GLint m_translationUniformRef{};
    GLint m_baseColorUniformRef{};
    UVec3 m_translation{};
    UVec3 m_baseColor{};
};

int main() {
    Test_2_09().run();
    return 0;
}
