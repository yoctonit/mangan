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

class StencilTesting {
private:
    Mn::ShaderInfo shader{};
    Mn::ShaderInfo shaderSingleColor{};
    Mn::Mesh cube1;
    Mn::Mesh cube2;
    Mn::Mesh cube1Outline;
    Mn::Mesh cube2Outline;
    Mn::Mesh floor;

    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    StencilTesting() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        shader = {"shader/stencil_testing.vs", "shader/stencil_testing.fs"};
        Mn::Connection cubeConnection(Mn::Box(), Mn::Geometry::Type::PositionsAndTexCoords, shader);
        Mn::Texture marbleTexture("images/marble.jpg");

        cube1 = Mn::Mesh(shader, cubeConnection);
        cube1.AddTexture(marbleTexture, 0);
        cube1.material["texture1"] = 0;
        cube2 = cube1;

        shaderSingleColor = {"shader/stencil_single_color.vs", "shader/stencil_single_color.fs"};
        Mn::Connection singleColorConnection(Mn::Box(), Mn::Geometry::Type::Positions, shaderSingleColor);

        cube1Outline = Mn::Mesh(shaderSingleColor, singleColorConnection);
        cube2Outline = cube1Outline;

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

        floor.material["view"] = view;
        floor.material["projection"] = projection;
        floor.material["model"] = glm::mat4(1.0f);

        cube1.material["view"] = view;
        cube1.material["projection"] = projection;
        cube1.material["model"] = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -1.0f));

        // outline of cube1 is slightly scaled
        float scale = 1.1f;
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        cube1Outline.material["view"] = view;
        cube1Outline.material["projection"] = projection;
        cube1Outline.material["model"] = model;

        cube2.material["view"] = view;
        cube2.material["projection"] = projection;
        cube2.material["model"] = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));

        // outline of cube2 is slightly scaled
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(scale, scale, scale));
        cube2Outline.material["view"] = view;
        cube2Outline.material["projection"] = projection;
        cube2Outline.material["model"] = model;
    }

    [[nodiscard]] bool IsRunning() const {
        return runScene;
    }

    void Render() const {
        // don't forget to clear the stencil buffer!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Draw floor as normal, but don't write the floor to the stencil buffer,
        // we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
        glStencilMask(0x00);
        floor.Draw();

        // 1st. render pass, draw objects as normal, writing to the stencil buffer
        // --------------------------------------------------------------------
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        cube1.Draw();
        cube2.Draw();

        // 2nd. render pass: now draw slightly scaled versions of the objects, this time disabling stencil writing.
        // Because the stencil buffer is now filled with several 1s, the parts of the buffer that are 1 are not drawn,
        // thus only drawing the objects' size differences, making it look like borders.
        // ------------------------------------------------------------------------------------------------------------
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        cube1Outline.Draw();
        cube2Outline.Draw();

        // reset stencil settings
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        glEnable(GL_DEPTH_TEST);
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<StencilTesting>(wnd);
    return 0;
}
