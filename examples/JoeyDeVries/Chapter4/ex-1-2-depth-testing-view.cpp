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

class DepthTestingView {
private:
    Mn::ShaderInfo shader{};
    Mn::Mesh cube1;
    Mn::Mesh cube2;
    Mn::Mesh floor;

    Camera camera{glm::vec3(0.0f, 0.5f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    DepthTestingView() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        shader = {"shader/depth_testing_view.vs", "shader/depth_testing_view.fs"};
        Mn::Connection cubeConnection(Mn::Box(), Mn::Geometry::Type::Positions, shader);

        cube1 = Mn::Mesh(shader, cubeConnection);
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
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cube1.Draw();
        cube2.Draw();
        floor.Draw();
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<DepthTestingView>(wnd);
    return 0;
}
