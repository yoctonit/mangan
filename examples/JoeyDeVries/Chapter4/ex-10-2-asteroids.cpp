#include "window/Run.h"
#include "core/Shader.h"
#include "core/Vao.h"
#include "core/Vbo.h"
#include "core/Texture.h"
#include "graphics/Uniform.h"
#include "geometry/Sphere.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Geometry Shader Example");
    wnd.CaptureCursor();

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    glEnable(GL_DEPTH_TEST);

    Mn::Shader shader(
            "shader/instancing_mvp.vs",
            "shader/instancing_mvp.fs"
    );

    Mn::Sphere sphere{};

    Mn::Vbo bufferPlanet{sphere.Data(Mn::Geometry::Type::PositionsAndTexCoords)};
    Mn::Vao vaoPlanet{true};
    vaoPlanet.Connect(bufferPlanet, 0, 3, 5, 0);
    vaoPlanet.Connect(bufferPlanet, 2, 2, 5, 3);
    Mn::Texture planetTexture("images/sandy_planet.png");

    Mn::Uniform uPlanetTex{shader.Locate("texture_diffuse1"), GL_SAMPLER_2D};
    Mn::Uniform uPlanetModel{shader.Locate("model"), GL_FLOAT_MAT4};
    Mn::Uniform uPlanetProjection{shader.Locate("projection"), GL_FLOAT_MAT4};
    Mn::Uniform uPlanetView{shader.Locate("view"), GL_FLOAT_MAT4};
    uPlanetTex = 0;

    Mn::Vbo bufferRock{sphere.Data(Mn::Geometry::Type::PositionsAndNormals)};
    Mn::Vao vaoRock{true};
    vaoRock.Connect(bufferRock, 0, 3, 5, 0);
    vaoRock.Connect(bufferRock, 2, 2, 5, 3);
    Mn::Texture rockTexture("images/rock.png");

    Mn::Uniform uRockTex{shader.Locate("texture_diffuse1"), GL_SAMPLER_2D};
    Mn::Uniform uRockModel{shader.Locate("model"), GL_FLOAT_MAT4};
    Mn::Uniform uRockProjection{shader.Locate("projection"), GL_FLOAT_MAT4};
    Mn::Uniform uRockView{shader.Locate("view"), GL_FLOAT_MAT4};
    uRockTex = 0;

    uPlanetModel = glm::mat4(1.0f);
    uRockModel = glm::mat4(1.0f);

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    unsigned int amount = 1000;
    glm::mat4 *modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(13); // initialize random seed
    float radius = 20.0f;
    float offset = 2.5f;
    for (unsigned int i = 0; i < amount; i++) {
        auto model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float) i / (float) amount * 360.0f;
        float displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float x = std::sin(angle) * radius + displacement;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float z = std::cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        auto scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        auto rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    auto &input = Mn::Window::GetInput();

    while (wnd.IsOpen()) {
        Mn::Window::PollEvents();

        input.Update();
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            wnd.Close();
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

        // configure transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        uPlanetProjection = projection;
        uRockProjection = projection;
        uPlanetView = view;
        uRockView = view;

        // draw planet
        shader.Use();
        planetTexture.Activate();
        uPlanetModel.Upload();
        uPlanetProjection.Upload();
        uPlanetView.Upload();
        uPlanetTex.Upload();
        vaoPlanet.Draw(GL_TRIANGLES, 0, sphere.VertexCount());

        // draw meteorites
        rockTexture.Activate();
        for (unsigned int i = 0; i < amount; i++) {
            uRockModel = modelMatrices[i];
            uRockModel.Upload();
            uRockProjection.Upload();
            uRockView.Upload();
            uRockTex.Upload();
            vaoRock.Draw(GL_TRIANGLES, 0, sphere.VertexCount());
        }
        wnd.Display();
    }

    return 0;
}
