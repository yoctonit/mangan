#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Uniform.h"
#include "graphics/Vao.h"
#include "graphics/Vbo.h"
#include "graphics/Texture.h"
#include "geometry/Box.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Geometry Shader Example");

    bool runScene = true;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);

    Mn::Shader shader(
            "shader/geometry_shader_2.vs",
            "shader/geometry_shader_2.fs",
            "shader/geometry_shader_2.gs"
    );

    Mn::Box box{};
    Mn::Vbo buffer{box.Data(Mn::Geometry::Type::PositionsAndTexCoords)};
    Mn::Vao vao{true};
    vao.Connect(buffer, 0, 3, 5, 0);
    vao.Connect(buffer, 2, 2, 5, 3);
    Mn::Texture marbleTexture("images/container2.png");
    Mn::Uniform uTex{shader.Locate("texture_diffuse1"), GL_SAMPLER_2D};
    Mn::Uniform uModel{shader.Locate("model"), GL_FLOAT_MAT4};
    Mn::Uniform uProjection{shader.Locate("projection"), GL_FLOAT_MAT4};
    Mn::Uniform uView{shader.Locate("view"), GL_FLOAT_MAT4};
    Mn::Uniform uTime{shader.Locate("time"), GL_FLOAT};
    uTex = 0;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 1.0f, 100.0f);
    uProjection = projection;
    auto model = glm::mat4(1.0f);
    uModel = model;

    auto &input = Mn::Window::GetInput();

    while (wnd.IsOpen() && runScene) {
        Mn::Window::PollEvents();

        input.Update();
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

        time += 0.016f;
        deltaTime = time - lastFrame;
        lastFrame = time;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();
        uView = view;
        uTime = time;

        shader.Use();
        marbleTexture.Activate();
        uModel.Upload();
        uProjection.Upload();
        uView.Upload();
        uTex.Upload();
        uTime.Upload();

        vao.Draw(GL_TRIANGLES, 0, 36);

        wnd.Display();
    }

    return 0;
}
