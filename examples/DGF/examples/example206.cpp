//
// Created by ivan on 27.9.2021..
//
#include "../core/base.h"
#include "../core/openGLUtils.h"
#include "../core/attribute.h"
#include "../core/uniform.h"

// render two triangles with different positions and colors
class Test : public Base {
public:
    Test() : Base() {}

    void initialize() override {
        std::string vsCode = R"(
        #version 460 core
        in vec3 position;
        uniform vec3 translation;
        void main()
        {
            vec3 pos = position + translation;
            gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
        }
        )";

        std::string fsCode = R"(
        #version 460 core
        uniform vec3 baseColor;
        out vec4 fragColor;
        void main()
        {
            fragColor = vec4(baseColor.r, baseColor.g, baseColor.b, 1.0);
        }
        )";

        programRef = OpenGLUtils::initializeProgram(vsCode, fsCode);

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
        translation1 = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{-0.5, 0.0, 0.0});
        translation1.locateVariable(programRef, "translation");

        translation2 = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{0.5, 0.0, 0.0});
        translation2.locateVariable(programRef, "translation");

        baseColor1 = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{1.0, 0.0, 0.0});
        baseColor1.locateVariable(programRef, "baseColor");

        baseColor2 = Uniform(Uniform::Type::Vec3, std::vector<GLfloat>{0.0, 0.0, 1.0});
        baseColor2.locateVariable(programRef, "baseColor");
    }

    void update() override {
        glUseProgram(programRef);

        // draw the first triangle
        translation1.uploadData();
        baseColor1.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

        // draw the second triangle
        translation2.uploadData();
        baseColor2.uploadData();
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

private:
    GLuint programRef{};
    GLuint vaoRef{};
    GLsizei vertexCount{};
    Uniform translation1{};
    Uniform translation2{};
    Uniform baseColor1{};
    Uniform baseColor2{};
};

int main() {
    Test scene;
    scene.run();
}
