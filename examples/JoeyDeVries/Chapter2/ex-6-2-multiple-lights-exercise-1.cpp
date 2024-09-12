#include <vector>
#include "engine/Run.h"
#include "graphics/ShaderInfo.h"
// #include "graphics/VboInfo.h"
#include "graphics/Connection.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "geometry/Box.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class CoordinateSystems {
private:
    Mn::ShaderInfo objectShader{};
    std::vector<Mn::Mesh> objects;

    Mn::ShaderInfo lightCubeShader{};
    std::vector<Mn::Mesh> lightCubes;

    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> pointLightPositions;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};
    int sceneIndex{};

    // scenes settings
    void DesertScene(Mn::ShaderInfo &shaderInfo) {
        glClearColor(0.75f, 0.52f, 0.3f, 1.0f);

        std::vector<glm::vec3> pointLightColors{
                glm::vec3(1.0f, 0.6f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0, 0.0),
                glm::vec3(0.2f, 0.2f, 1.0f)
        };
        shaderInfo["material.diffuse"] = 0;
        shaderInfo["material.specular"] = 1;
        shaderInfo["material.shininess"] = 32.0f;

        shaderInfo["dirLight.direction"] = glm::vec3(-0.2f, -1.0f, -0.3f);
        shaderInfo["dirLight.ambient"] = glm::vec3(0.3f, 0.24f, 0.14f);
        shaderInfo["dirLight.diffuse"] = glm::vec3(0.7f, 0.42f, 0.26f);
        shaderInfo["dirLight.specular"] = glm::vec3(0.5f, 0.5f, 0.5f);

        shaderInfo["pointLights[0].position"] = pointLightPositions[0];
        shaderInfo["pointLights[0].ambient"] = 0.1f * pointLightColors[0];
        shaderInfo["pointLights[0].diffuse"] = pointLightColors[0];
        shaderInfo["pointLights[0].specular"] = pointLightColors[0];
        shaderInfo["pointLights[0].constant"] = 1.0f;
        shaderInfo["pointLights[0].linear"] = 0.09f;
        shaderInfo["pointLights[0].quadratic"] = 0.032f;

        shaderInfo["pointLights[1].position"] = pointLightPositions[1];
        shaderInfo["pointLights[1].ambient"] = 0.1f * pointLightColors[1];
        shaderInfo["pointLights[1].diffuse"] = pointLightColors[1];
        shaderInfo["pointLights[1].specular"] = pointLightColors[1];
        shaderInfo["pointLights[1].constant"] = 1.0f;
        shaderInfo["pointLights[1].linear"] = 0.09f;
        shaderInfo["pointLights[1].quadratic"] = 0.032f;

        shaderInfo["pointLights[2].position"] = pointLightPositions[2];
        shaderInfo["pointLights[2].ambient"] = 0.1f * pointLightColors[2];
        shaderInfo["pointLights[2].diffuse"] = pointLightColors[2];
        shaderInfo["pointLights[2].specular"] = pointLightColors[2];
        shaderInfo["pointLights[2].constant"] = 1.0f;
        shaderInfo["pointLights[2].linear"] = 0.09f;
        shaderInfo["pointLights[2].quadratic"] = 0.032f;

        shaderInfo["pointLights[3].position"] = pointLightPositions[3];
        shaderInfo["pointLights[3].ambient"] = 0.1f * pointLightColors[3];
        shaderInfo["pointLights[3].diffuse"] = pointLightColors[3];
        shaderInfo["pointLights[3].specular"] = pointLightColors[3];
        shaderInfo["pointLights[3].constant"] = 1.0f;
        shaderInfo["pointLights[3].linear"] = 0.09f;
        shaderInfo["pointLights[3].quadratic"] = 0.032f;

        shaderInfo["spotLight.ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
        shaderInfo["spotLight.diffuse"] = glm::vec3(0.8f, 0.8f, 0.0f);
        shaderInfo["spotLight.specular"] = glm::vec3(0.8f, 0.8f, 0.0f);
        shaderInfo["spotLight.constant"] = 1.0f;
        shaderInfo["spotLight.linear"] = 0.09f;
        shaderInfo["spotLight.quadratic"] = 0.032f;
        shaderInfo["spotLight.cutOff"] = glm::cos(glm::radians(12.5f));
        shaderInfo["spotLight.outerCutOff"] = glm::cos(glm::radians(13.0f));
    }

    void DesertScenePointLightColors() {
        std::vector<glm::vec3> pointLightColors{
                glm::vec3(1.0f, 0.6f, 0.0f),
                glm::vec3(1.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0, 0.0),
                glm::vec3(0.2f, 0.2f, 1.0f)
        };
        for (unsigned int i = 0; i < 4; i++) {
            lightCubes[i].material["lightColor"] = pointLightColors[i];
        }
    }

    void FactoryScene(Mn::ShaderInfo &shaderInfo) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.2f, 0.2f, 0.6f),
                glm::vec3(0.3f, 0.3f, 0.7f),
                glm::vec3(0.0f, 0.0f, 0.3f),
                glm::vec3(0.4f, 0.4f, 0.4f)
        };

        shaderInfo["material.diffuse"] = 0;
        shaderInfo["material.specular"] = 1;
        shaderInfo["material.shininess"] = 32.0f;

        shaderInfo["dirLight.direction"] = glm::vec3(-0.2f, -1.0f, -0.3f);
        shaderInfo["dirLight.ambient"] = glm::vec3(0.05f, 0.05f, 0.1f);
        shaderInfo["dirLight.diffuse"] = glm::vec3(0.2f, 0.2f, 0.7f);
        shaderInfo["dirLight.specular"] = glm::vec3(0.7f, 0.7f, 0.7f);

        shaderInfo["pointLights[0].position"] = pointLightPositions[0];
        shaderInfo["pointLights[0].ambient"] = 0.1f * pointLightColors[0];
        shaderInfo["pointLights[0].diffuse"] = pointLightColors[0];
        shaderInfo["pointLights[0].specular"] = pointLightColors[0];
        shaderInfo["pointLights[0].constant"] = 1.0f;
        shaderInfo["pointLights[0].linear"] = 0.09f;
        shaderInfo["pointLights[0].quadratic"] = 0.032f;

        shaderInfo["pointLights[1].position"] = pointLightPositions[1];
        shaderInfo["pointLights[1].ambient"] = 0.1f * pointLightColors[1];
        shaderInfo["pointLights[1].diffuse"] = pointLightColors[1];
        shaderInfo["pointLights[1].specular"] = pointLightColors[1];
        shaderInfo["pointLights[1].constant"] = 1.0f;
        shaderInfo["pointLights[1].linear"] = 0.09f;
        shaderInfo["pointLights[1].quadratic"] = 0.032f;

        shaderInfo["pointLights[2].position"] = pointLightPositions[2];
        shaderInfo["pointLights[2].ambient"] = 0.1f * pointLightColors[2];
        shaderInfo["pointLights[2].diffuse"] = pointLightColors[2];
        shaderInfo["pointLights[2].specular"] = pointLightColors[2];
        shaderInfo["pointLights[2].constant"] = 1.0f;
        shaderInfo["pointLights[2].linear"] = 0.09f;
        shaderInfo["pointLights[2].quadratic"] = 0.032f;

        shaderInfo["pointLights[3].position"] = pointLightPositions[3];
        shaderInfo["pointLights[3].ambient"] = 0.1f * pointLightColors[3];
        shaderInfo["pointLights[3].diffuse"] = pointLightColors[3];
        shaderInfo["pointLights[3].specular"] = pointLightColors[3];
        shaderInfo["pointLights[3].constant"] = 1.0f;
        shaderInfo["pointLights[3].linear"] = 0.09f;
        shaderInfo["pointLights[3].quadratic"] = 0.032f;

        shaderInfo["spotLight.ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
        shaderInfo["spotLight.diffuse"] = glm::vec3(1.0f, 1.0f, 1.0f);
        shaderInfo["spotLight.specular"] = glm::vec3(1.0f, 1.0f, 1.0f);
        shaderInfo["spotLight.constant"] = 1.0f;
        shaderInfo["spotLight.linear"] = 0.009f;
        shaderInfo["spotLight.quadratic"] = 0.0032f;
        shaderInfo["spotLight.cutOff"] = glm::cos(glm::radians(10.0f));
        shaderInfo["spotLight.outerCutOff"] = glm::cos(glm::radians(12.5f));
    }

    void FactoryScenePointLightColors() {
        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.2f, 0.2f, 0.6f),
                glm::vec3(0.3f, 0.3f, 0.7f),
                glm::vec3(0.0f, 0.0f, 0.3f),
                glm::vec3(0.4f, 0.4f, 0.4f)
        };
        for (unsigned int i = 0; i < 4; i++) {
            lightCubes[i].material["lightColor"] = pointLightColors[i];
        }
    }

    void HorrorScene(Mn::ShaderInfo &shaderInfo) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.3f, 0.1f, 0.1f)
        };

        shaderInfo["material.diffuse"] = 0;
        shaderInfo["material.specular"] = 1;
        shaderInfo["material.shininess"] = 32.0f;

        shaderInfo["dirLight.direction"] = glm::vec3(-0.2f, -1.0f, -0.3f);
        shaderInfo["dirLight.ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
        shaderInfo["dirLight.diffuse"] = glm::vec3(0.05f, 0.05f, 0.05f);
        shaderInfo["dirLight.specular"] = glm::vec3(0.2f, 0.2f, 0.2f);

        shaderInfo["pointLights[0].position"] = pointLightPositions[0];
        shaderInfo["pointLights[0].ambient"] = 0.1f * pointLightColors[0];
        shaderInfo["pointLights[0].diffuse"] = pointLightColors[0];
        shaderInfo["pointLights[0].specular"] = pointLightColors[0];
        shaderInfo["pointLights[0].constant"] = 1.0f;
        shaderInfo["pointLights[0].linear"] = 0.14f;
        shaderInfo["pointLights[0].quadratic"] = 0.07f;

        shaderInfo["pointLights[1].position"] = pointLightPositions[1];
        shaderInfo["pointLights[1].ambient"] = 0.1f * pointLightColors[1];
        shaderInfo["pointLights[1].diffuse"] = pointLightColors[1];
        shaderInfo["pointLights[1].specular"] = pointLightColors[1];
        shaderInfo["pointLights[1].constant"] = 1.0f;
        shaderInfo["pointLights[1].linear"] = 0.14f;
        shaderInfo["pointLights[1].quadratic"] = 0.07f;

        shaderInfo["pointLights[2].position"] = pointLightPositions[2];
        shaderInfo["pointLights[2].ambient"] = 0.1f * pointLightColors[2];
        shaderInfo["pointLights[2].diffuse"] = pointLightColors[2];
        shaderInfo["pointLights[2].specular"] = pointLightColors[2];
        shaderInfo["pointLights[2].constant"] = 1.0f;
        shaderInfo["pointLights[2].linear"] = 0.22f;
        shaderInfo["pointLights[2].quadratic"] = 0.20f;

        shaderInfo["pointLights[3].position"] = pointLightPositions[3];
        shaderInfo["pointLights[3].ambient"] = 0.1f * pointLightColors[3];
        shaderInfo["pointLights[3].diffuse"] = pointLightColors[3];
        shaderInfo["pointLights[3].specular"] = pointLightColors[3];
        shaderInfo["pointLights[3].constant"] = 1.0f;
        shaderInfo["pointLights[3].linear"] = 0.14f;
        shaderInfo["pointLights[3].quadratic"] = 0.07f;

        shaderInfo["spotLight.ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
        shaderInfo["spotLight.diffuse"] = glm::vec3(0.8f, 0.8f, 0.0f);
        shaderInfo["spotLight.specular"] = glm::vec3(0.8f, 0.8f, 0.0f);
        shaderInfo["spotLight.constant"] = 1.0f;
        shaderInfo["spotLight.linear"] = 0.09f;
        shaderInfo["spotLight.quadratic"] = 0.032f;
        shaderInfo["spotLight.cutOff"] = glm::cos(glm::radians(12.5f));
        shaderInfo["spotLight.outerCutOff"] = glm::cos(glm::radians(15.0f));
    }

    void HorrorScenePointLightColors() {
        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3(0.3f, 0.1f, 0.1f)
        };
        for (unsigned int i = 0; i < 4; i++) {
            lightCubes[i].material["lightColor"] = pointLightColors[i];
        }
    }

    void BiomechanicalLabScene(Mn::ShaderInfo &shaderInfo) {
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f)
        };

        shaderInfo["material.diffuse"] = 0;
        shaderInfo["material.specular"] = 1;
        shaderInfo["material.shininess"] = 32.0f;

        shaderInfo["dirLight.direction"] = glm::vec3(-0.2f, -1.0f, -0.3f);
        shaderInfo["dirLight.ambient"] = glm::vec3(0.5f, 0.5f, 0.5f);
        shaderInfo["dirLight.diffuse"] = glm::vec3(1.0f, 1.0f, 1.0f);
        shaderInfo["dirLight.specular"] = glm::vec3(1.0f, 1.0f, 1.0f);

        shaderInfo["pointLights[0].position"] = pointLightPositions[0];
        shaderInfo["pointLights[0].ambient"] = 0.1f * pointLightColors[0];
        shaderInfo["pointLights[0].diffuse"] = pointLightColors[0];
        shaderInfo["pointLights[0].specular"] = pointLightColors[0];
        shaderInfo["pointLights[0].constant"] = 1.0f;
        shaderInfo["pointLights[0].linear"] = 0.07f;
        shaderInfo["pointLights[0].quadratic"] = 0.017f;

        shaderInfo["pointLights[1].position"] = pointLightPositions[1];
        shaderInfo["pointLights[1].ambient"] = 0.1f * pointLightColors[1];
        shaderInfo["pointLights[1].diffuse"] = pointLightColors[1];
        shaderInfo["pointLights[1].specular"] = pointLightColors[1];
        shaderInfo["pointLights[1].constant"] = 1.0f;
        shaderInfo["pointLights[1].linear"] = 0.07f;
        shaderInfo["pointLights[1].quadratic"] = 0.017f;

        shaderInfo["pointLights[2].position"] = pointLightPositions[2];
        shaderInfo["pointLights[2].ambient"] = 0.1f * pointLightColors[2];
        shaderInfo["pointLights[2].diffuse"] = pointLightColors[2];
        shaderInfo["pointLights[2].specular"] = pointLightColors[2];
        shaderInfo["pointLights[2].constant"] = 1.0f;
        shaderInfo["pointLights[2].linear"] = 0.07f;
        shaderInfo["pointLights[2].quadratic"] = 0.017f;

        shaderInfo["pointLights[3].position"] = pointLightPositions[3];
        shaderInfo["pointLights[3].ambient"] = 0.1f * pointLightColors[3];
        shaderInfo["pointLights[3].diffuse"] = pointLightColors[3];
        shaderInfo["pointLights[3].specular"] = pointLightColors[3];
        shaderInfo["pointLights[3].constant"] = 1.0f;
        shaderInfo["pointLights[3].linear"] = 0.07f;
        shaderInfo["pointLights[3].quadratic"] = 0.017f;

        shaderInfo["spotLight.ambient"] = glm::vec3(0.0f, 0.0f, 0.0f);
        shaderInfo["spotLight.diffuse"] = glm::vec3(0.0f, 1.0f, 0.0f);
        shaderInfo["spotLight.specular"] = glm::vec3(0.0f, 1.0f, 0.0f);
        shaderInfo["spotLight.constant"] = 1.0f;
        shaderInfo["spotLight.linear"] = 0.07f;
        shaderInfo["spotLight.quadratic"] = 0.017f;
        shaderInfo["spotLight.cutOff"] = glm::cos(glm::radians(7.0f));
        shaderInfo["spotLight.outerCutOff"] = glm::cos(glm::radians(10.0f));
    }

    void BiomechanicalLabScenePointLightColors() {
        std::vector<glm::vec3> pointLightColors = {
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f),
                glm::vec3(0.4f, 0.7f, 0.1f)
        };
        for (unsigned int i = 0; i < 4; i++) {
            lightCubes[i].material["lightColor"] = pointLightColors[i];
        }
    }

public:
    CoordinateSystems() {
        cubePositions = {
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(2.0f, 5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3(2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f, 3.0f, -7.5f),
                glm::vec3(1.3f, -2.0f, -2.5f),
                glm::vec3(1.5f, 2.0f, -2.5f),
                glm::vec3(1.5f, 0.2f, -1.5f),
                glm::vec3(-1.3f, 1.0f, -1.5f)
        };

        // positions of the point lights
        pointLightPositions = {
                glm::vec3(0.7f, 0.2f, 2.0f),
                glm::vec3(2.3f, -3.3f, -4.0f),
                glm::vec3(-4.0f, 2.0f, -12.0f),
                glm::vec3(0.0f, 0.0f, -3.0f)
        };

        // configure global opengl state
        glEnable(GL_DEPTH_TEST);

        objectShader = {
                "shader/lighting_maps_1.vs",
                "shader/multiple_lights.fs"
        };

        Mn::VboInfo buffer(Mn::Box(),Mn::Geometry::Type::PositionsNormalsAndTexCoords);
        Mn::Connection objectConnection;
        objectConnection.ConnectBuffer(buffer, Mn::Geometry::Type::PositionsNormalsAndTexCoords, objectShader);

        Mn::Mesh obj(objectShader, objectConnection);
        obj.AddTexture(Mn::Texture("images/container2.png"), 0);
        obj.AddTexture(Mn::Texture("images/container2_specular.png"), 1);

        for (unsigned int i = 0; i < 10; i++) {
            objects.push_back(obj);
        }

        lightCubeShader = {
                "shader/colors.vs",
                "shader/light_cube_exercise_1.fs"
        };
        Mn::Connection lightCubeConnection;
        lightCubeConnection.ConnectBuffer(buffer.Buffer(), buffer.ElementCount(),
                                          lightCubeShader.Location(Mn::ShaderInfo::AttributeType::Position),
                                          3, 8, 0);
        Mn::Mesh lightCube(lightCubeShader, lightCubeConnection);

        for (unsigned int i = 0; i < 4; i++) {
            lightCubes.push_back(lightCube);
        }
    }

    void Update(const Mn::Input &input) {
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

        if (input.IsClickedKey(MN_KEY_N)) {
            sceneIndex++;
            if (sceneIndex > 3) {
                sceneIndex = 0;
            }
            switch (sceneIndex) {
                case 0:
                    std::cout << "selected desert scene\n";
                    break;
                case 1:
                    std::cout << "selected factory scene\n";
                    break;
                case 2:
                    std::cout << "selected horror scene\n";
                    break;
                case 3:
                    std::cout << "selected biomechanical lab scene\n";
                    break;
            }
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

        auto view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();

        // note: currently we set the projection matrix each frame,
        // but since the projection matrix rarely changes
        // it's often best practice to set it outside the main loop only once.
        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);

        for (unsigned int i = 0; i < 10; i++) {
            switch (sceneIndex) {
                case 0:
                    DesertScene(objects[i].material);
                    DesertScenePointLightColors();
                    break;
                case 1:
                    FactoryScene(objects[i].material);
                    FactoryScenePointLightColors();
                    break;
                case 2:
                    HorrorScene(objects[i].material);
                    HorrorScenePointLightColors();
                    break;
                case 3:
                    BiomechanicalLabScene(objects[i].material);
                    BiomechanicalLabScenePointLightColors();
                    break;
            }

            // set dynamic uniforms
            objects[i].material["spotLight.position"] = camera.Position;
            objects[i].material["spotLight.direction"] = camera.Front;
            objects[i].material["viewPos"] = camera.Position;

            objects[i].material["view"] = view;
            objects[i].material["projection"] = projection;

            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (float) i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = time * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objects[i].material["model"] = model;
        }

        for (unsigned int i = 0; i < 4; i++) {
            auto model = glm::translate(glm::mat4(1.0f), pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubes[i].material["model"] = model;
            lightCubes[i].material["view"] = view;
            lightCubes[i].material["projection"] = projection;
        }
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw box objects
        objectShader.Upload();
        for (unsigned int i = 0; i < 10; i++) {
            objects[i].Draw();
        }

        // also draw the lamp object(s)
        lightCubeShader.Upload();
        for (unsigned int i = 0; i < 4; i++) {
            lightCubes[i].Draw();
        }
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<CoordinateSystems>(wnd);
    return 0;
}
