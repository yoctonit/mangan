#include "engine/Run.h"
#include "graphics/ShaderInfo.h"
#include "graphics/Connection.h"
#include "graphics/Texture.h"
#include "graphics/TextureCubeMap.h"
#include "graphics/Mesh.h"
#include "geometry/Box.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class DepthTesting {
private:
    Mn::ShaderInfo shader{};
    Mn::ShaderInfo skyboxShader{};
    Mn::Mesh cube;
    Mn::Mesh skyBox;
    Mn::TextureCubeMap cubeMapTexture{};

    Camera camera{glm::vec3(0.0f, 0.5f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    DepthTesting() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shader = {"shader/cubemaps_environment.vs", "shader/cubemaps_environment.fs"};
        skyboxShader = {"shader/skybox.vs", "shader/skybox.fs"};

        Mn::Connection cubeConnection(Mn::Box(), Mn::Geometry::Type::PositionsAndNormals, shader);
//        Mn::Texture marbleTexture("images/marble.jpg");

        cube = Mn::Mesh(shader, cubeConnection);
//        cube.AddTexture(marbleTexture, 0);
        cube.material["skybox"] = 0;

        Mn::Connection skyBoxConnection(Mn::Box(), Mn::Geometry::Type::Positions, skyboxShader);

        skyBox = Mn::Mesh(skyboxShader, skyBoxConnection);
        skyBox.material["skybox"] = 0;
        skyBox.renderSettings.Set(Mn::RenderSettings::Type::DoubleSide, true);
//        skyboxShader.Debug();

        cubeMapTexture = Mn::TextureCubeMap(
                {
                        "images/right.jpg",
                        "images/left.jpg",
                        "images/top.jpg",
                        "images/bottom.jpg",
                        "images/front.jpg",
                        "images/back.jpg"
                }
        );
//        cubeMapTexture.Debug("cube map texture");
//        Mn::TextureCubeMap::DebugRefCnt();
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

        cube.material["view"] = view;
        cube.material["projection"] = projection;
        cube.material["model"] = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
        cube.material["cameraPos"] = camera.Position;

        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyBox.material["view"] = view;
        skyBox.material["projection"] = projection;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw scene as normal
        cube.Draw();

        // draw skybox as last
        // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture.Id());
        cubeMapTexture.Activate();
        skyBox.Draw();
        glDepthFunc(GL_LESS); // set depth function back to default
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<DepthTesting>(wnd);
    return 0;
}
