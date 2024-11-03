#include "window/Window.h"
#include "core/Texture.h"
#include "core/Vao.h"
#include "core/Vbo.h"
#include "graphics/ShaderInfo.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;


int main() {
    Mn::Window wnd{SCR_WIDTH, SCR_HEIGHT, "Blinn Lighting"};

    bool blinn = false;
    bool blinnKeyPressed = true;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};
    float lastFrame{};

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Mn::ShaderInfo shader{"shader/blinn.vs.glsl", "shader/blinn.fs.glsl"};

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> planeVertices{
            // positions            // normals         // texcoords
            10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
            -10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
            -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,

            10.0f, -0.5f, 10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 0.0f,
            -10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 0.0f, 10.0f,
            10.0f, -0.5f, -10.0f, 0.0f, 1.0f, 0.0f, 10.0f, 10.0f
    };
    Mn::Vao planeVao{true};
    Mn::Vbo planeVbo{planeVertices};
    planeVao.Connect(planeVbo, 0, 3, 8, 0);
    planeVao.Connect(planeVbo, 1, 3, 8, 3);
    planeVao.Connect(planeVbo, 2, 2, 8, 6);

    Mn::Texture floorTexture{"images/wood.png"};
    shader["floorTexture"] = 0;

//    shader.Debug();

    // lighting info
    // -------------
    glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

    auto &input = Mn::Window::GetInput();
    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();
        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
            continue;
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

        if (input.IsClickedKey(MN_KEY_B)) {
            blinn = !blinn;
            blinnKeyPressed = true;
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

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader["projection"] = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        shader["view"] = camera.GetViewMatrix();
        // set light uniforms
        shader["viewPos"] = camera.Position;
        shader["lightPos"] = lightPos;
        shader["blinn"] = blinn;
        shader.Upload();
        planeVao.Draw(GL_TRIANGLES, 0, 6);

        if (blinnKeyPressed) {
            std::cout << (blinn ? "Blinn-Phong" : "Phong") << std::endl;
            blinnKeyPressed = false;
        }

        wnd.Display();
    }

    return 0;
}
