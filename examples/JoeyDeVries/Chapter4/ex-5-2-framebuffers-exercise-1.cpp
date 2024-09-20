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

class Framebuffers {
private:
    Mn::ShaderInfo shader{};
    Mn::ShaderInfo screenShader{};
    Mn::Mesh cube1;
    Mn::Mesh cube2;
    Mn::Mesh floor;
    Mn::Mesh quad;
    unsigned int framebuffer{};
    unsigned int textureColorBuffer{};

    Camera camera{glm::vec3(0.0f, 0.5f, 3.0f)};

    // timing
    float time{};
    float deltaTime{};    // time between current frame and last frame
    float lastFrame{};

    bool runScene{true};

public:
    Framebuffers() {
        // configure global opengl state
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);

        shader = {"shader/framebuffers.vs", "shader/framebuffers.fs"};
        screenShader = {"shader/framebuffers_screen.vs", "shader/framebuffers_screen.fs"};

        Mn::Connection cubeConnection(Mn::Box(), Mn::Geometry::Type::PositionsAndTexCoords, shader);
        Mn::Texture marbleTexture("images/container.jpg");

        cube1 = Mn::Mesh(shader, cubeConnection);
        cube1.AddTexture(marbleTexture, 0);
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

        std::vector<float> quadVertices{ // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
                // positions   // texCoords
                -0.3f, 1.0f, 0.0f, 1.0f,
                -0.3f, 0.7f, 0.0f, 0.0f,
                0.3f, 0.7f, 1.0f, 0.0f,

                -0.3f, 1.0f, 0.0f, 1.0f,
                0.3f, 0.7f, 1.0f, 0.0f,
                0.3f, 1.0f, 1.0f, 1.0f
        };
        Mn::Vbo quadVbo(quadVertices);
        Mn::Connection quadConnection;
        quadConnection.ConnectBuffer(quadVbo, 6, 0, 2, 4, 0);
        quadConnection.ConnectBuffer(quadVbo, 6, 1, 2, 4, 2);
        quad = Mn::Mesh(screenShader, quadConnection);
        quad.material["screenTexture"] = 0;

        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        // create a color attachment texture
        glGenTextures(1, &textureColorBuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH,
                              SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER,
                                  rbo); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

    void Render() {
        // first render pass: mirror texture.
        // bind to framebuffer and draw to color texture as we normally
        // would, but with the view camera reversed.
        // bind to framebuffer and draw scene as we normally would to color texture
        // ------------------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

        // make sure we clear the framebuffer's content
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto model = glm::mat4(1.0f);
        camera.Yaw += 180.0f; // rotate the camera's yaw 180 degrees around
        camera.ProcessMouseMovement(0, 0,
                                    false); // call this to make sure it updates its camera vectors, note that we disable pitch constrains for this specific case (otherwise we can't reverse camera's pitch values)
        glm::mat4 view = camera.GetViewMatrix();
        camera.Yaw -= 180.0f; // reset it back to its original orientation
        camera.ProcessMouseMovement(0, 0, true);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        cube1.material["view"] = view;
        cube1.material["projection"] = projection;
        cube2.material["view"] = view;
        cube2.material["projection"] = projection;
        floor.material["view"] = view;
        floor.material["projection"] = projection;

        cube1.Draw();
        cube2.Draw();
        floor.Draw();

        // second render pass: draw as normal
        // ----------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = camera.GetViewMatrix();
        cube1.material["view"] = view;
        cube2.material["view"] = view;
        floor.material["view"] = view;

        cube1.Draw();
        cube2.Draw();
        floor.Draw();

        // now draw the mirror quad with screen texture
        // --------------------------------------------
        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        glBindTexture(GL_TEXTURE_2D,
                      textureColorBuffer);    // use the color attachment texture as the texture of the quad plane
        quad.Draw();
    }
};

int main() {
    Mn::Window wnd(SCR_WIDTH, SCR_HEIGHT, "Camera Class Example");
    wnd.CaptureCursor();
    Mn::ShowScene<Framebuffers>(wnd);
    return 0;
}
