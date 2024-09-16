#include <vector>
#include "engine/Run.h"
#include "graphics/ShaderInfo.h"
#include "graphics/Connection.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "geometry/Box.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class BlendingDiscard {
private:
    Mn::ShaderInfo shader{};
    Mn::Mesh cube1;
    Mn::Mesh cube2;
    Mn::Mesh floor;
    std::vector<Mn::Mesh> windows;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    std::vector<glm::vec3> windowPositions;
    bool runScene{true};

public:
    BlendingDiscard() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shader = {"shader/blending.vs", "shader/blending.fs"};
        Mn::Connection cubeConnection(Mn::Box(), Mn::Geometry::Type::PositionsAndTexCoords, shader);

        cube1 = Mn::Mesh(shader, cubeConnection);
        cube1.AddTexture(Mn::Texture("images/marble.jpg"), 0);
        cube1.material["texture1"] = 0;

        cube2 = cube1;

        std::vector<float> planeVertices{
                // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
                5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
                -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
                -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,

                5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
                5.0f, -0.5f, -5.0f, 2.0f, 2.0f,
                -5.0f, -0.5f, -5.0f, 0.0f, 2.0f
        };
        Mn::Vbo planeVbo(planeVertices);
        Mn::Connection planeConnection;
        planeConnection.ConnectBuffer(planeVbo, 6, 0, 3, 5, 0);
        planeConnection.ConnectBuffer(planeVbo, 6, 1, 2, 5, 3);
        floor = Mn::Mesh(shader, planeConnection);
        floor.AddTexture(Mn::Texture("images/metal.png"), 0);
        floor.material["texture1"] = 0;

        std::vector<float> transparentVertices{
                // positions         // texture Coords (swapped y coordinates because texture is flipped upside down)
                0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.0f, -0.5f, 0.0f, 0.0f, 0.0f,
                1.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
                1.0f, -0.5f, 0.0f, 1.0f, 0.0f,
                1.0f, 0.5f, 0.0f, 1.0f, 1.0f
        };
        Mn::Vbo transparentVbo(transparentVertices);
        Mn::Connection transparentConnection;
        transparentConnection.ConnectBuffer(transparentVbo, 6, 0, 3, 5, 0);
        transparentConnection.ConnectBuffer(transparentVbo, 6, 1, 2, 5, 3);
        Mn::Mesh window(shader, transparentConnection);
        Mn::Texture windowTex("images/window.png");
        windowTex.SetParameters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);
        window.AddTexture(windowTex, 0);
        window.material["texture1"] = 0;
        window.renderSettings.Set(Mn::RenderSettings::Type::DoubleSide, true);

        for (int i = 0; i < 5; i++) {
            windows.push_back(window);
        }

        // transparent window locations
        // --------------------------------
        windowPositions = {
                glm::vec3(-1.5f, 0.0f, -0.48f),
                glm::vec3(1.5f, 0.0f, 0.51f),
                glm::vec3(0.0f, 0.0f, 0.7f),
                glm::vec3(-0.3f, 0.0f, -2.3f),
                glm::vec3(0.5f, 0.0f, -0.6f)
        };
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
        auto view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();

        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);

        cube1.material["view"] = view;
        cube1.material["projection"] = projection;
        cube1.material["model"] = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));

        cube2.material["view"] = view;
        cube2.material["projection"] = projection;
        cube2.material["model"] = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

        floor.material["view"] = view;
        floor.material["projection"] = projection;
        floor.material["model"] = glm::mat4(1.0f);

        // sort the transparent windows before rendering
        // ---------------------------------------------
        std::map<float, glm::vec3> sorted;
        for (auto windowPosition : windowPositions){
            float distance = glm::length(camera.Position - windowPosition);
            sorted[distance] = windowPosition;
        }

        int i = 0;
        for (auto it = sorted.rbegin(); it != sorted.rend(); ++it)
        {
            auto model = glm::translate(glm::mat4(1.0f), it->second);
            windows[i].material["view"] = view;
            windows[i].material["projection"] = projection;
            windows[i].material["model"] = model;
            ++i;
        }

    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube1.Draw();
        cube2.Draw();
        floor.Draw();
        for (int i = 0; i < 5; i++) {
            windows[i].Draw();
        }
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<BlendingDiscard>(wnd);
    return 0;
}
