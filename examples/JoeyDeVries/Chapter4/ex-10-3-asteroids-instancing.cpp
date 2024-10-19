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

    Camera camera{glm::vec3(0.0f, 0.0f, 155.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    glEnable(GL_DEPTH_TEST);

    Mn::Shader planetShader(
            "shader/instancing_mvp.vs",
            "shader/instancing_mvp.fs"
    );
    Mn::Shader asteroidShader(
            "shader/instancing_mvp_asteroids.vs",
            "shader/instancing_mvp.fs"
    );

    Mn::Sphere sphere{};

    Mn::Vbo bufferPlanet{sphere.Data(Mn::Geometry::Type::PositionsAndTexCoords)};
    Mn::Vao vaoPlanet{true};
    vaoPlanet.Connect(bufferPlanet, 0, 3, 5, 0);
    vaoPlanet.Connect(bufferPlanet, 2, 2, 5, 3);
    Mn::Texture planetTexture("images/sandy_planet.png");

    Mn::Uniform uPlanetTex{planetShader.Locate("texture_diffuse1"), GL_SAMPLER_2D};
    Mn::Uniform uPlanetModel{planetShader.Locate("model"), GL_FLOAT_MAT4};
    Mn::Uniform uPlanetProjection{planetShader.Locate("projection"), GL_FLOAT_MAT4};
    Mn::Uniform uPlanetView{planetShader.Locate("view"), GL_FLOAT_MAT4};
    uPlanetTex = 0;
    uPlanetModel = glm::scale(glm::mat4(1.0f), glm::vec3{10.0f, 10.0f, 10.0f});

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    int amount = 10000;
    glm::mat4 *modelMatrices;
    modelMatrices = new glm::mat4[amount];
    srand(13); // initialize random seed
    float radius = 150.0f;
    float offset = 25.0f;
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

    Mn::Vbo bufferRock{sphere.Data(Mn::Geometry::Type::PositionsAndTexCoords)};

    // configure instanced array
    // -------------------------
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    Mn::Vao vaoRock{true};
    vaoRock.Connect(bufferRock, 0, 3, 5, 0);
    vaoRock.Connect(bufferRock, 2, 2, 5, 3);
    // glBindVertexArray(vaoRock.Id());
    // set attribute pointers for matrix (4 times vec4)
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) 0);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (sizeof(glm::vec4)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *) (3 * sizeof(glm::vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

//    glBindVertexArray(0);

    Mn::Texture rockTexture("images/rock.png");

    Mn::Uniform uRockTex{asteroidShader.Locate("texture_diffuse1"), GL_SAMPLER_2D};
    Mn::Uniform uRockProjection{asteroidShader.Locate("projection"), GL_FLOAT_MAT4};
    Mn::Uniform uRockView{asteroidShader.Locate("view"), GL_FLOAT_MAT4};
    uRockTex = 0;

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
        planetShader.Use();
        planetTexture.Activate();
        uPlanetModel.Upload();
        uPlanetProjection.Upload();
        uPlanetView.Upload();
        uPlanetTex.Upload();
        vaoPlanet.Draw(GL_TRIANGLES, 0, sphere.VertexCount());

        // draw meteorites
        rockTexture.Activate();
        asteroidShader.Use();
        uRockProjection.Upload();
        uRockView.Upload();
        uRockTex.Upload();
        vaoRock.Activate();
        glDrawArraysInstanced(GL_TRIANGLES, 0, sphere.VertexCount(), amount);

        wnd.Display();
    }

    delete[]modelMatrices;
    return 0;
}
