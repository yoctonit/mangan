#include "core/Base.h"
#include "core/Shader.h"
#include "core/Attribute.h"
#include "core/Uniform.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>

class Test_3_02 : public Base {
public:
    void initialize() override {
        m_programRef = Shader::FromFiles("shader/Test_3_02.vert", "shader/Test_3_02.frag").id();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &m_vaoRef);
        glBindVertexArray(m_vaoRef);

        const std::vector<GLfloat> positionData{
                0.0f, 0.2f, 0.0f,
                0.1f, -0.2f, 0.0f,
                -0.1f, -0.2f, 0.0f
        };
        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(m_programRef, "position");

        // set up uniforms
        m_uniformModel = Uniform(m_programRef, "modelMatrix",
                                 glm::translate(glm::vec3(0.0f, 0.0f, -1.0f)));
        m_uniformProjection = Uniform(m_programRef, "projectionMatrix",
                                      glm::perspective(glm::radians(60.f), 1.0f, 0.1f, 100.0f));

        // movement speed, units per second
        moveSpeed = 0.5f;
        // rotation speed, radians per second
        turnSpeed = 1.57f;
    }

    void update() override {
        auto moveAmount = (float) (moveSpeed * m_deltaTimeSeconds);
        auto turnAmount = (float) (turnSpeed * m_deltaTimeSeconds);

        // global
        if (m_input.isPressedKey(MN_KEY_W)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(0.0f, moveAmount, 0.0f)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_S)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(0.0f, -moveAmount, 0.0f)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_A)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(-moveAmount, 0.0f, 0.0f)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_D)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(moveAmount, 0.0f, 0.0f)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_Z)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(0.0f, 0.0f, moveAmount)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_X)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::translate(glm::vec3(0.0f, 0.0f, -moveAmount)) * m_uniformModel.data().m_dataMat4x4;
        }

        if (m_input.isPressedKey(MN_KEY_Q)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::rotate(turnAmount, glm::vec3(0.0f, 0.0f, 1.0f)) * m_uniformModel.data().m_dataMat4x4;
        }
        if (m_input.isPressedKey(MN_KEY_E)) {
            m_uniformModel.data().m_dataMat4x4 =
                    glm::rotate(-turnAmount, glm::vec3(0.0f, 0.0f, 1.0f)) * m_uniformModel.data().m_dataMat4x4;
        }

        // local
        if (m_input.isPressedKey(MN_KEY_I)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::translate(glm::vec3(0.0f, moveAmount, 0.0f));
        }
        if (m_input.isPressedKey(MN_KEY_K)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::translate(glm::vec3(0.0f, -moveAmount, 0.0f));
        }
        if (m_input.isPressedKey(MN_KEY_J)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::translate(glm::vec3(-moveAmount, 0.0f, 0.0f));
        }
        if (m_input.isPressedKey(MN_KEY_L)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::translate(glm::vec3(moveAmount, 0.0f, 0.0f));
        }

        if (m_input.isPressedKey(MN_KEY_U)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::rotate(turnAmount, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (m_input.isPressedKey(MN_KEY_O)) {
            m_uniformModel.data().m_dataMat4x4 *= glm::rotate(-turnAmount, glm::vec3(0.0f, 0.0f, 1.0f));
        }

        // render scene

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(m_programRef);
        glBindVertexArray(m_vaoRef);

        m_uniformModel.upload();
        m_uniformProjection.upload();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

private:
    double moveSpeed{};
    double turnSpeed{};

    GLuint m_programRef{};
    GLuint m_vaoRef{};
    Uniform m_uniformModel{};
    Uniform m_uniformProjection{};
};

int main() {
    Test_3_02().run();
    return 0;
}
