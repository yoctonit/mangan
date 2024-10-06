#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vao.h"
#include "graphics/Vbo.h"
#include "graphics/Uniform.h"
#include "geometry/Box.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class GlslUbo {
private:
    Mn::Shader shaderRed{};
    Mn::Shader shaderGreen{};
    Mn::Shader shaderBlue{};
    Mn::Shader shaderYellow{};

    Mn::Uniform modelRedUniform;
    Mn::Uniform modelGreenUniform;
    Mn::Uniform modelBlueUniform;
    Mn::Uniform modelYellowUniform;

    Mn::Vao mVao;
    Mn::Vbo mBuffer;
    unsigned int mUboMatrices{};

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    GlslUbo() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shaderRed = {"shader/advanced_glsl.vs", "shader/red.fs"};
        shaderGreen = {"shader/advanced_glsl.vs", "shader/green.fs"};
        shaderBlue = {"shader/advanced_glsl.vs", "shader/blue.fs"};
        shaderYellow = {"shader/advanced_glsl.vs", "shader/yellow.fs"};

        modelRedUniform = Mn::Uniform(
                shaderRed.Locate("model"),
                GL_FLOAT_MAT4
        );
        modelGreenUniform = Mn::Uniform(
                shaderGreen.Locate("model"),
                GL_FLOAT_MAT4
        );
        modelBlueUniform = Mn::Uniform(
                shaderBlue.Locate("model"),
                GL_FLOAT_MAT4
        );
        modelYellowUniform = Mn::Uniform(
                shaderYellow.Locate("model"),
                GL_FLOAT_MAT4
        );

        Mn::Box box{};
        mVao = Mn::Vao(true);
        mBuffer = Mn::Vbo{box.Data(Mn::Geometry::Type::Positions)};
        mVao.Connect(mBuffer, 0, 3, 3, 0);

        unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(shaderRed.Id(), "Matrices");
        unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(shaderGreen.Id(), "Matrices");
        unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(shaderBlue.Id(), "Matrices");
        unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(shaderYellow.Id(), "Matrices");
        // then we link each shader's uniform block to this uniform binding point
        glUniformBlockBinding(shaderRed.Id(), uniformBlockIndexRed, 0);
        glUniformBlockBinding(shaderGreen.Id(), uniformBlockIndexGreen, 0);
        glUniformBlockBinding(shaderBlue.Id(), uniformBlockIndexBlue, 0);
        glUniformBlockBinding(shaderYellow.Id(), uniformBlockIndexYellow, 0);
        // Now actually create the buffer
        glGenBuffers(1, &mUboMatrices);
        glBindBuffer(GL_UNIFORM_BUFFER, mUboMatrices);
        glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
        // define the range of the buffer that links to a uniform binding point
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, mUboMatrices, 0, 2 * sizeof(glm::mat4));

        // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
        glm::mat4 projection = glm::perspective(45.0f, (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        glBindBuffer(GL_UNIFORM_BUFFER, mUboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void Update(const Mn::Input &input) {
        // input (camera movement) logic
        // --------------------
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        if (input.IsPressedKey(MN_KEY_W)) {
            camera.ProcessKeyboard(Camera::Movement::Forward, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_S)) {
            camera.ProcessKeyboard(Camera::Movement::Backward, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_A)) {
            camera.ProcessKeyboard(Camera::Movement::Left, deltaTime);
        }
        if (input.IsPressedKey(MN_KEY_D)) {
            camera.ProcessKeyboard(Camera::Movement::Right, deltaTime);
        }

        auto mouseOffset = input.GetMouseOffset();
        camera.ProcessMouseMovement(mouseOffset.x, mouseOffset.y);

        auto scrollOffset = input.GetMouseScroll();
        camera.ProcessMouseScroll(scrollOffset.y);

        // per-frame time logic
        // --------------------
        time += 0.016f;
        deltaTime = time - lastFrame;
        lastFrame = time;

        // transformations
        // --------------------
        // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
        glm::mat4 view = camera.GetViewMatrix();
        glBindBuffer(GL_UNIFORM_BUFFER, mUboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        auto model = glm::mat4(1.0f);
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
        modelRedUniform = model;

        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
        modelGreenUniform = model;

        model = glm::translate(glm::mat4(1.0f), glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
        modelYellowUniform = model;

        model = glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
        modelBlueUniform = model;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw 4 cubes
        mVao.Activate();

        shaderRed.Use();
        modelRedUniform.Upload();
        mVao.Draw(GL_TRIANGLES, 0, 36);

        shaderGreen.Use();
        modelGreenUniform.Upload();
        mVao.Draw(GL_TRIANGLES, 0, 36);

        shaderYellow.Use();
        modelYellowUniform.Upload();
        mVao.Draw(GL_TRIANGLES, 0, 36);

        shaderBlue.Use();
        modelBlueUniform.Upload();
        mVao.Draw(GL_TRIANGLES, 0, 36);
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<GlslUbo>(wnd);
    return 0;
}
