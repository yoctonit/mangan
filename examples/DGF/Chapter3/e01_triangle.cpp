#include "core/run.h"
#include "core/shader.h"
#include "core/input.h"
#include "core/attribute.h"
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Triangle3d {
public:
    Triangle3d() = default;

    ~Triangle3d() = default;

    void initialize(int, int) {
        programRef = Mn::Shader::CreateFromFiles(
                "shader/shape3d.vert",
                "shader/shape3d.frag"
        );
        ml = Mn::Shader::Uniform(programRef, "modelMatrix");
        pl = Mn::Shader::Uniform(programRef, "projectionMatrix");
//        pl = glGetUniformLocation(programRef, "projectionMatrix");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        const std::vector<GLfloat> positionData{
                0.0f, 0.2f, 0.0f,
                0.1f, -0.2f, 0.0f,
                -0.1f, -0.2f, 0.0f
        };
        vertexCount = static_cast<GLsizei>(positionData.size()) / 3;

        Mn::Attribute positionAttribute(Mn::Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(programRef, "position");

        m = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
        p = glm::perspective(60.0f, 1.0f, 0.1f, 1000.0f);
        moveSpeed = 0.5f;
        turnSpeed = 1.57f;
    }

    void draw() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programRef);
        glBindVertexArray(vaoRef);
//        glUniformMatrix4fv(ml, 1, GL_FALSE, glm::value_ptr(m));
        ml.uploadMatrix(glm::value_ptr(m));
//        glUniformMatrix4fv(pl, 1, GL_FALSE, glm::value_ptr(p));
        pl.uploadMatrix(glm::value_ptr(p));
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    void update(const Mn::Input &input, double delta_time) {
        float moveAmount = moveSpeed * (float) delta_time;
        float turnAmount = turnSpeed * (float) delta_time;

        // global
        if (input.is_pressed(Mn::key::w)) {
            m = glm::translate(glm::vec3(0.0f, moveAmount, 0.0f)) * m;
        }
        if (input.is_pressed(Mn::key::s)) {
            m = glm::translate(glm::vec3(0.0f, -moveAmount, 0.0f)) * m;
        }
        if (input.is_pressed(Mn::key::a)) {
            m = glm::translate(glm::vec3(-moveAmount, 0.0f, 0.0f)) * m;
        }
        if (input.is_pressed(Mn::key::d)) {
            m = glm::translate(glm::vec3(moveAmount, 0.0f, 0.0f)) * m;
        }
        if (input.is_pressed(Mn::key::z)) {
            m = glm::translate(glm::vec3(0.0f, 0.0f, moveAmount)) * m;
        }
        if (input.is_pressed(Mn::key::x)) {
            m = glm::translate(glm::vec3(0.0f, 0.0f, -moveAmount)) * m;
        }

        if (input.is_pressed(Mn::key::q)) {
            m = glm::rotate(turnAmount, glm::vec3(0.0f, 0.0f, 1.0f)) * m;
        }
        if (input.is_pressed(Mn::key::e)) {
            m = glm::rotate(-turnAmount, glm::vec3(0.0f, 0.0f, 1.0f)) * m;
        }

        // local
        if (input.is_pressed(Mn::key::up)) {
            m *= glm::translate(glm::vec3(0.0f, moveAmount, 0.0f));
        }
        if (input.is_pressed(Mn::key::down)) {
            m *= glm::translate(glm::vec3(0.0f, -moveAmount, 0.0f));
        }
        if (input.is_pressed(Mn::key::left)) {
            m *= glm::translate(glm::vec3(-moveAmount, 0.0f, 0.0f));
        }
        if (input.is_pressed(Mn::key::right)) {
            m *= glm::translate(glm::vec3(moveAmount, 0.0f, 0.0f));
        }

        if (input.is_pressed(Mn::key::u)) {
            m *= glm::rotate(turnAmount, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (input.is_pressed(Mn::key::o)) {
            m *= glm::rotate(-turnAmount, glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }

    void cleanup() {}

private:
    GLuint programRef{};
    GLuint vaoRef{};
    GLsizei vertexCount{};
    glm::mat4 m{};
    glm::mat4 p{};
//    GLint ml{};
//    GLint pl{};
    Mn::Shader::Uniform ml{};
    Mn::Shader::Uniform pl{};
    float moveSpeed{};
    float turnSpeed{};
};

int main() {
    Mn::Window window(800, 800, "Triangle3d");
    Triangle3d scene;
    Mn::Run<Triangle3d>(scene, window);
    return 0;
}
