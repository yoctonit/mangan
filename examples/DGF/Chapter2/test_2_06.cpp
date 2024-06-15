#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"
#include "core/Uniform.h"

typedef UniformVec3<std::vector<float>> UVec3;

class Test_2_06 : public Base {
public:
    void initialize() override {
        // load code, send to GPU, and compile; store program reference
        m_programRef = Shader::FromFiles("shader/Test_2_06.vert", "shader/Test_2_06.frag").id();

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

        m_translation1 = UVec3(std::vector<float>{-0.5f, 0.0f, 0.0f});
        m_baseColor1 = UVec3(std::vector<float>{1.0f, 0.0f, 0.0f});

        m_translation2 = UVec3(std::vector<float>{0.5f, 0.0f, 0.0f});
        m_baseColor2 = UVec3(std::vector<float>{0.0f, 0.0f, 1.0f});
    }

    void update() override {
        glUseProgram(m_programRef);
        glBindVertexArray(m_vaoRef);

        // draw the first triangle
        m_translation1.upload(m_translationUniformRef);
        m_baseColor1.upload(m_baseColorUniformRef);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw the second triangle
        m_translation2.upload(m_translationUniformRef);
        m_baseColor2.upload(m_baseColorUniformRef);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    GLuint m_programRef{};
    GLuint m_vaoRef{};

    GLint m_translationUniformRef{};
    GLint m_baseColorUniformRef{};
    UVec3 m_translation1{};
    UVec3 m_translation2{};
    UVec3 m_baseColor1{};
    UVec3 m_baseColor2{};
};

int main() {
    Test_2_06().run();
    return 0;
}
