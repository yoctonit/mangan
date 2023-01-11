//
// Created by ivan on 27.9.2021..
//
#include "../core/base.h"
#include "../core/openGLUtils.h"
#include "../core/attribute.h"
#include "../core/uniform.h"

// animate triangle moving across screen
class Test : public Base {
public:
    Test() : Base() {}

    void initialize() override {
        std::string vsCode = R"(
        #version 430 core
        in vec3 position;
        uniform vec3 translation;
        void main()
        {
            vec3 pos = position + translation;
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        }
        )";

        std::string fsCode = R"(
        #version 430 core
        uniform vec3 baseColor;
        out vec4 fragColor;
        void main()
        {
            fragColor = vec4(baseColor.r, baseColor.g, baseColor.b, 1.0);
        }
        )";

        programRef = OpenGLUtils::initializeProgram(vsCode, fsCode);

        // render settings (optional)

        // specify color used when clearing screen
        glClearColor(0.0, 0.0, 0.0, 1.0);

        // set up vertex array object
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        // set up vertex attributes
        const std::vector<GLfloat> positionData{
                0.0f, 0.2f, 0.0f,
                0.2f, -0.2f, 0.0f,
                -0.2f, -0.2f, 0.0f
        };
        vertexCount = static_cast<GLsizei>(positionData.size()) / 3;

        Attribute positionAttribute(Attribute::Type::Vec3, positionData);
        positionAttribute.associateVariable(programRef, "position");

        // set up uniforms
        translation = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{-0.5, 0.0, 0.0});
        translation.locateVariable(programRef, "translation");

        baseColor = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{1.0, 0.0, 0.0});
        baseColor.locateVariable(programRef, "baseColor");
    }

    void update() override {
        // update data

        // increase x coordinate of translation
        translation.Vector()[0] += 0.01;
        // if triangle passes off-screen on the right,
        // change translation, so it reappears on the left
        if (translation.Vector()[0] > 1.2)
            translation.Vector()[0] = -1.2;

        // render scene

        // reset color buffer with specified color
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programRef);
        translation.uploadData();
        baseColor.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

private:
    GLuint programRef{};
    GLuint vaoRef{};
    GLsizei vertexCount{};
    Uniform translation{};
    Uniform baseColor{};
};

int main() {
    Test scene;
    scene.run();
}
