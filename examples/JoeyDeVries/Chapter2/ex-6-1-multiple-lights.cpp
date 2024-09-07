#include <vector>
#include "engine/Run.h"
#include "graphics/Shader.h"
#include "graphics/Vbo.h"
#include "graphics/Vao.h"
#include "graphics/Uniform.h"
#include "graphics/Texture.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

class CoordinateSystems {
private:
    Mn::Shader shader{};
    Mn::Vbo vbo{};
    Mn::Vao vao{};

    Mn::Uniform viewUniform{};
    Mn::Uniform projectionUniform{};
    std::vector<Mn::Uniform> modelUniform;

    Mn::Uniform materialDiffuseUniform{};
    Mn::Uniform materialSpecularUniform{};
    Mn::Uniform materialShininessUniform{};

    Mn::Uniform dirLightDirectionUniform{};
    Mn::Uniform dirLightAmbientUniform{};
    Mn::Uniform dirLightDiffuseUniform{};
    Mn::Uniform dirLightSpecularUniform{};

    Mn::Uniform pointLight0PositionUniform{};
    Mn::Uniform pointLight0AmbientUniform{};
    Mn::Uniform pointLight0DiffuseUniform{};
    Mn::Uniform pointLight0SpecularUniform{};
    Mn::Uniform pointLight0ConstantUniform{};
    Mn::Uniform pointLight0LinearUniform{};
    Mn::Uniform pointLight0QuadraticUniform{};

    Mn::Uniform pointLight1PositionUniform{};
    Mn::Uniform pointLight1AmbientUniform{};
    Mn::Uniform pointLight1DiffuseUniform{};
    Mn::Uniform pointLight1SpecularUniform{};
    Mn::Uniform pointLight1ConstantUniform{};
    Mn::Uniform pointLight1LinearUniform{};
    Mn::Uniform pointLight1QuadraticUniform{};

    Mn::Uniform pointLight2PositionUniform{};
    Mn::Uniform pointLight2AmbientUniform{};
    Mn::Uniform pointLight2DiffuseUniform{};
    Mn::Uniform pointLight2SpecularUniform{};
    Mn::Uniform pointLight2ConstantUniform{};
    Mn::Uniform pointLight2LinearUniform{};
    Mn::Uniform pointLight2QuadraticUniform{};

    Mn::Uniform pointLight3PositionUniform{};
    Mn::Uniform pointLight3AmbientUniform{};
    Mn::Uniform pointLight3DiffuseUniform{};
    Mn::Uniform pointLight3SpecularUniform{};
    Mn::Uniform pointLight3ConstantUniform{};
    Mn::Uniform pointLight3LinearUniform{};
    Mn::Uniform pointLight3QuadraticUniform{};

    Mn::Uniform spotLightPositionUniform{};
    Mn::Uniform spotLightDirectionUniform{};
    Mn::Uniform spotLightAmbientUniform{};
    Mn::Uniform spotLightDiffuseUniform{};
    Mn::Uniform spotLightSpecularUniform{};
    Mn::Uniform spotLightConstantUniform{};
    Mn::Uniform spotLightLinearUniform{};
    Mn::Uniform spotLightQuadraticUniform{};
    Mn::Uniform spotLightCutOffUniform{};
    Mn::Uniform spotLightOuterCutOffUniform{};

    Mn::Uniform viewPosUniform{};

    Mn::Shader lightCubeShader{};
    Mn::Vao lightCubeVao{};

    // uniforms for lightCubeShader
    std::vector<Mn::Uniform> lightCubeModelUniform;
    Mn::Uniform lightCubeViewUniform{};
    Mn::Uniform lightCubeProjectionUniform{};
    std::vector<Mn::Uniform> lightCubeColorUniform{};

    Mn::Texture tex1{};
    Mn::Texture tex2{};

    std::vector<glm::vec3> cubePositions;
    std::vector<glm::vec3> pointLightPositions;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // lighting
    glm::vec3 lightPos{1.2f, 1.0f, 2.0f};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

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
        // -----------------------------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shader = {
                "shader/lighting_maps_1.vs",
                "shader/multiple_lights.fs"
        };

        for (unsigned int i = 0; i < 10; i++) {
            modelUniform.emplace_back(
                    shader.Locate("model"),
                    Mn::Uniform::Type::Mat4x4
            );
        }
        viewUniform.Create(shader.Locate("view"), Mn::Uniform::Type::Mat4x4);
        projectionUniform.Create(shader.Locate("projection"), Mn::Uniform::Type::Mat4x4);

        materialDiffuseUniform.Create(shader.Locate("material.diffuse"), Mn::Uniform::Type::Int);
        materialDiffuseUniform = 0;
        materialSpecularUniform.Create(shader.Locate("material.specular"), Mn::Uniform::Type::Int);
        materialSpecularUniform = 1;
        materialShininessUniform.Create(shader.Locate("material.shininess"), Mn::Uniform::Type::Float);
        materialShininessUniform = 32.0f;

        dirLightDirectionUniform.Create(shader.Locate("dirLight.direction"), Mn::Uniform::Type::Vec3);
        dirLightAmbientUniform.Create(shader.Locate("dirLight.ambient"), Mn::Uniform::Type::Vec3);
        dirLightDiffuseUniform.Create(shader.Locate("dirLight.diffuse"), Mn::Uniform::Type::Vec3);
        dirLightSpecularUniform.Create(shader.Locate("dirLight.specular"), Mn::Uniform::Type::Vec3);

        pointLight0PositionUniform.Create(shader.Locate("pointLights[0].position"), Mn::Uniform::Type::Vec3);
        pointLight0AmbientUniform.Create(shader.Locate("pointLights[0].ambient"), Mn::Uniform::Type::Vec3);
        pointLight0DiffuseUniform.Create(shader.Locate("pointLights[0].diffuse"), Mn::Uniform::Type::Vec3);
        pointLight0SpecularUniform.Create(shader.Locate("pointLights[0].specular"), Mn::Uniform::Type::Vec3);
        pointLight0ConstantUniform.Create(shader.Locate("pointLights[0].constant"), Mn::Uniform::Type::Float);
        pointLight0LinearUniform.Create(shader.Locate("pointLights[0].linear"), Mn::Uniform::Type::Float);
        pointLight0QuadraticUniform.Create(shader.Locate("pointLights[0].quadratic"), Mn::Uniform::Type::Float);

        pointLight1PositionUniform.Create(shader.Locate("pointLights[1].position"), Mn::Uniform::Type::Vec3);
        pointLight1AmbientUniform.Create(shader.Locate("pointLights[1].ambient"), Mn::Uniform::Type::Vec3);
        pointLight1DiffuseUniform.Create(shader.Locate("pointLights[1].diffuse"), Mn::Uniform::Type::Vec3);
        pointLight1SpecularUniform.Create(shader.Locate("pointLights[1].specular"), Mn::Uniform::Type::Vec3);
        pointLight1ConstantUniform.Create(shader.Locate("pointLights[1].constant"), Mn::Uniform::Type::Float);
        pointLight1LinearUniform.Create(shader.Locate("pointLights[1].linear"), Mn::Uniform::Type::Float);
        pointLight1QuadraticUniform.Create(shader.Locate("pointLights[1].quadratic"), Mn::Uniform::Type::Float);

        pointLight2PositionUniform.Create(shader.Locate("pointLights[2].position"), Mn::Uniform::Type::Vec3);
        pointLight2AmbientUniform.Create(shader.Locate("pointLights[2].ambient"), Mn::Uniform::Type::Vec3);
        pointLight2DiffuseUniform.Create(shader.Locate("pointLights[2].diffuse"), Mn::Uniform::Type::Vec3);
        pointLight2SpecularUniform.Create(shader.Locate("pointLights[2].specular"), Mn::Uniform::Type::Vec3);
        pointLight2ConstantUniform.Create(shader.Locate("pointLights[2].constant"), Mn::Uniform::Type::Float);
        pointLight2LinearUniform.Create(shader.Locate("pointLights[2].linear"), Mn::Uniform::Type::Float);
        pointLight2QuadraticUniform.Create(shader.Locate("pointLights[2].quadratic"), Mn::Uniform::Type::Float);

        pointLight3PositionUniform.Create(shader.Locate("pointLights[3].position"), Mn::Uniform::Type::Vec3);
        pointLight3AmbientUniform.Create(shader.Locate("pointLights[3].ambient"), Mn::Uniform::Type::Vec3);
        pointLight3DiffuseUniform.Create(shader.Locate("pointLights[3].diffuse"), Mn::Uniform::Type::Vec3);
        pointLight3SpecularUniform.Create(shader.Locate("pointLights[3].specular"), Mn::Uniform::Type::Vec3);
        pointLight3ConstantUniform.Create(shader.Locate("pointLights[3].constant"), Mn::Uniform::Type::Float);
        pointLight3LinearUniform.Create(shader.Locate("pointLights[3].linear"), Mn::Uniform::Type::Float);
        pointLight3QuadraticUniform.Create(shader.Locate("pointLights[3].quadratic"), Mn::Uniform::Type::Float);

        spotLightPositionUniform.Create(shader.Locate("spotLight.position"), Mn::Uniform::Type::Vec3);
        spotLightDirectionUniform.Create(shader.Locate("spotLight.direction"), Mn::Uniform::Type::Vec3);
        spotLightAmbientUniform.Create(shader.Locate("spotLight.ambient"), Mn::Uniform::Type::Vec3);
        spotLightDiffuseUniform.Create(shader.Locate("spotLight.diffuse"), Mn::Uniform::Type::Vec3);
        spotLightSpecularUniform.Create(shader.Locate("spotLight.specular"), Mn::Uniform::Type::Vec3);
        spotLightConstantUniform.Create(shader.Locate("spotLight.constant"), Mn::Uniform::Type::Float);
        spotLightLinearUniform.Create(shader.Locate("spotLight.linear"), Mn::Uniform::Type::Float);
        spotLightQuadraticUniform.Create(shader.Locate("spotLight.quadratic"), Mn::Uniform::Type::Float);
        spotLightCutOffUniform.Create(shader.Locate("spotLight.cutOff"), Mn::Uniform::Type::Float);
        spotLightOuterCutOffUniform.Create(shader.Locate("spotLight.outerCutOff"), Mn::Uniform::Type::Float);

        viewPosUniform.Create(shader.Locate("viewPos"), Mn::Uniform::Type::Vec3);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have.
           We have to set them manually and index the proper PointLight struct
           in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there,
           or by using a more efficient uniform approach by using 'Uniform buffer objects',
           but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        dirLightDirectionUniform = glm::vec3(-0.2f, -1.0f, -0.3f);
        dirLightAmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
        dirLightDiffuseUniform = glm::vec3(0.4f, 0.4f, 0.4f);
        dirLightSpecularUniform = glm::vec3(0.5f, 0.5f, 0.5f);

        pointLight0PositionUniform = pointLightPositions[0];
        pointLight0AmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLight0DiffuseUniform = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLight0SpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLight0ConstantUniform = 1.0f;
        pointLight0LinearUniform = 0.09f;
        pointLight0QuadraticUniform = 0.032f;

        pointLight1PositionUniform = pointLightPositions[1];
        pointLight1AmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLight1DiffuseUniform = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLight1SpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLight1ConstantUniform = 1.0f;
        pointLight1LinearUniform = 0.09f;
        pointLight1QuadraticUniform = 0.032f;

        pointLight2PositionUniform = pointLightPositions[2];
        pointLight2AmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLight2DiffuseUniform = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLight2SpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLight2ConstantUniform = 1.0f;
        pointLight2LinearUniform = 0.09f;
        pointLight2QuadraticUniform = 0.032f;

        pointLight3PositionUniform = pointLightPositions[3];
        pointLight3AmbientUniform = glm::vec3(0.05f, 0.05f, 0.05f);
        pointLight3DiffuseUniform = glm::vec3(0.8f, 0.8f, 0.8f);
        pointLight3SpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        pointLight3ConstantUniform = 1.0f;
        pointLight3LinearUniform = 0.09f;
        pointLight3QuadraticUniform = 0.032f;

        spotLightPositionUniform = camera.Position;
        spotLightDirectionUniform = camera.Front;
        spotLightAmbientUniform = glm::vec3(0.0f, 0.0f, 0.0f);
        spotLightDiffuseUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        spotLightSpecularUniform = glm::vec3(1.0f, 1.0f, 1.0f);
        spotLightConstantUniform = 1.0f;
        spotLightLinearUniform = 0.09f;
        spotLightQuadraticUniform = 0.032f;
        spotLightCutOffUniform = glm::cos(glm::radians(12.5f));
        spotLightOuterCutOffUniform = glm::cos(glm::radians(15.0f));

        lightCubeShader = {
                "shader/colors.vs",
                "shader/light_cube_exercise_1.fs"
        };
        for (unsigned int i = 0; i < 4; i++) {
            lightCubeModelUniform.emplace_back(
                    lightCubeShader.Locate("model"),
                    Mn::Uniform::Type::Mat4x4
            );
            lightCubeColorUniform.emplace_back(
                    lightCubeShader.Locate("lightColor"),
                    Mn::Uniform::Type::Vec3
            );
        }
        lightCubeViewUniform.Create(
                lightCubeShader.Locate("view"),
                Mn::Uniform::Type::Mat4x4
        );
        lightCubeProjectionUniform.Create(
                lightCubeShader.Locate("projection"),
                Mn::Uniform::Type::Mat4x4
        );

        vao.Create();

        std::vector<float> vertices{
                // positions          // normals           // texture coords
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };
        vbo = Mn::Vbo::FromData(vertices);

        // position attribute
        vao.Connect(0, 3, 8, 0);
        // normal attribute
        vao.Connect(1, 3, 8, 3);
        // texture coord attribute
        vao.Connect(2, 2, 8, 6);

        lightCubeVao.Create();
        // position attribute (buffer still bound)
        lightCubeVao.Connect(0, 3, 8, 0);

        // load and create a texture
        tex1 = Mn::Texture::FromImage("images/container2.png");
        tex2 = Mn::Texture::FromImage("images/container2_specular.png");
    }

    ~CoordinateSystems() {
        tex1.Release();
        tex2.Release();
        vbo.Release();
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            runScene = false;
        }

        // per-frame time logic
        // --------------------
        time += 0.016f;
        deltaTime = time - lastFrame;
        lastFrame = time;

        // create transformations
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

        // set dynamic uniforms
        spotLightPositionUniform = camera.Position;
        spotLightDirectionUniform = camera.Front;
        viewPosUniform = camera.Position;

        auto view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        viewUniform = view;
        lightCubeViewUniform = view;

        // note: currently we set the projection matrix each frame,
        // but since the projection matrix rarely changes
        // it's often best practice to set it outside the main loop only once.
        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(
                glm::radians(camera.Zoom),
                (float) SCR_WIDTH / (float) SCR_HEIGHT,
                0.1f, 100.0f);
        projectionUniform = projection;
        lightCubeProjectionUniform = projection;

        for (unsigned int i = 0; i < 10; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (float) i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = time * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            modelUniform[i] = model;
        }

        for (unsigned int i = 0; i < 4; i++) {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubeModelUniform[i] = model;
        }
        lightCubeColorUniform[0] = glm::vec3(1.0f, 0.0f, 0.0f);
        lightCubeColorUniform[1] = glm::vec3(0.0f, 1.0f, 0.0f);
        lightCubeColorUniform[2] = glm::vec3(0.0f, 0.0f, 1.0f);
        lightCubeColorUniform[3] = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex1.Activate(0);
        tex2.Activate(1);

        shader.Use();
        viewUniform.Upload();
        projectionUniform.Upload();

        materialDiffuseUniform.Upload();
        materialSpecularUniform.Upload();
        materialShininessUniform.Upload();

        dirLightDirectionUniform.Upload();
        dirLightAmbientUniform.Upload();
        dirLightDiffuseUniform.Upload();
        dirLightSpecularUniform.Upload();

        pointLight0PositionUniform.Upload();
        pointLight0AmbientUniform.Upload();
        pointLight0DiffuseUniform.Upload();
        pointLight0SpecularUniform.Upload();
        pointLight0ConstantUniform.Upload();
        pointLight0LinearUniform.Upload();
        pointLight0QuadraticUniform.Upload();

        pointLight1PositionUniform.Upload();
        pointLight1AmbientUniform.Upload();
        pointLight1DiffuseUniform.Upload();
        pointLight1SpecularUniform.Upload();
        pointLight1ConstantUniform.Upload();
        pointLight1LinearUniform.Upload();
        pointLight1QuadraticUniform.Upload();

        pointLight2PositionUniform.Upload();
        pointLight2AmbientUniform.Upload();
        pointLight2DiffuseUniform.Upload();
        pointLight2SpecularUniform.Upload();
        pointLight2ConstantUniform.Upload();
        pointLight2LinearUniform.Upload();
        pointLight2QuadraticUniform.Upload();

        pointLight3PositionUniform.Upload();
        pointLight3AmbientUniform.Upload();
        pointLight3DiffuseUniform.Upload();
        pointLight3SpecularUniform.Upload();
        pointLight3ConstantUniform.Upload();
        pointLight3LinearUniform.Upload();
        pointLight3QuadraticUniform.Upload();

        spotLightPositionUniform.Upload();
        spotLightDirectionUniform.Upload();
        spotLightCutOffUniform.Upload();
        spotLightOuterCutOffUniform.Upload();
        spotLightAmbientUniform.Upload();
        spotLightDiffuseUniform.Upload();
        spotLightSpecularUniform.Upload();
        spotLightConstantUniform.Upload();
        spotLightLinearUniform.Upload();
        spotLightQuadraticUniform.Upload();

        viewPosUniform.Upload();

        for (unsigned int i = 0; i < 10; i++) {
            modelUniform[i].Upload();
            vao.Draw(GL_TRIANGLES, 0, 36);
        }

        // also draw the lamp object(s)
        lightCubeShader.Use();
        lightCubeViewUniform.Upload();
        lightCubeProjectionUniform.Upload();

        // we now draw as many light bulbs as we have point lights.
        for (unsigned int i = 0; i < 4; i++) {
            lightCubeModelUniform[i].Upload();
            lightCubeColorUniform[i].Upload();
            lightCubeVao.Draw(GL_TRIANGLES, 0, 36);
        }
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<CoordinateSystems>(wnd);
    return 0;
}
