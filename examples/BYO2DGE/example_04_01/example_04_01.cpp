#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/Renderable.h"

class MyGame {
public:
    void initialize(int, int) {
        // Step A: Initialize the game engine
        engine = std::make_shared<Engine>();
        camera = std::make_shared<Camera>(
                glm::vec2(20.0f, 60.0f), // center of the WC
                20.0f, // width of WC
                glm::ivec4(20, 40, 600, 300) // viewport:orgX, orgY, W, H
        );

        // Step B: Create the Renderable objects:
        mWhiteSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mWhiteSq->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        mWhiteSq->getXform()->setPosition(20.0f, 60.0f);
        mWhiteSq->getXform()->setRotationInRad(0.2f); // In Radians
        mWhiteSq->getXform()->setSize(5.0f, 5.0f);

        mRedSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mRedSq->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
        mRedSq->getXform()->setPosition(20.0f, 60.0f);
        mRedSq->getXform()->setSize(2.0f, 2.0f);
    }

    void draw() const {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        camera->setViewAndCameraMatrix();

        mWhiteSq->draw(*camera);
        mRedSq->draw(*camera);
    }

    void update(const Mn::Input &, double) {
        // Simple game: move the white square and pulse the red
        std::shared_ptr<Transform> whiteXform = mWhiteSq->getXform();
        float deltaX = 0.05;
        // Step A: Rotate the white square
        if (whiteXform->getXPos() > 30.0f) // the right-bound of the window
            whiteXform->setPosition(10.0f, 60.0f);
        whiteXform->incXPosBy(deltaX);
        whiteXform->incRotationByDegree(1);
        // Step B: pulse the red square
        std::shared_ptr<Transform> redXform = mRedSq->getXform();
        if (redXform->getWidth() > 5.0f)
            redXform->setSize(2.0f, 2.0f);
        redXform->incSizeBy(0.05f);
    }

    void cleanup() {}

private:
    std::shared_ptr<Engine> engine;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Renderable> mWhiteSq;
    std::shared_ptr<Renderable> mRedSq;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    MyGame scene;
    Mn::Run<MyGame>(scene, window);
    return 0;
}
