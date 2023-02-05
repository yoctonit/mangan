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
        mBlueSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mBlueSq->setColor(glm::vec4(0.25f, 0.25f, 0.95f, 1.0f));
        mBlueSq->getXform()->setPosition(20.0f, 60.0f);
        mBlueSq->getXform()->setRotationInRad(0.2f); // In Radians
        mBlueSq->getXform()->setSize(5.0f, 5.0f);

        mRedSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mRedSq->setColor(glm::vec4(1.0f, 0.25f, 0.25f, 1.0f));
        mRedSq->getXform()->setPosition(20.0f, 60.0f);
        mRedSq->getXform()->setSize(2.0f, 2.0f);

        mTLSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mTLSq->setColor(glm::vec4(0.9f, 0.1f, 0.1f, 1.0f));
        mTLSq->getXform()->setPosition(10.0f, 65.0f);
        mTRSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mTRSq->setColor(glm::vec4(0.1f, 0.9f, 0.1f, 1.0f));
        mTRSq->getXform()->setPosition(30.0f, 65.0f);
        mBRSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mBRSq->setColor(glm::vec4(0.1f, 0.1f, 0.9f, 1.0f));
        mBRSq->getXform()->setPosition(30.0f, 55.0f);
        mBLSq = std::make_shared<Renderable>(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get()
        );
        mBLSq->setColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mBLSq->getXform()->setPosition(10.0f, 55.0f);
    }

    void draw() const {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);

        camera->setViewAndCameraMatrix();

        // Center Blue, slightly rotated square
        mBlueSq->draw(*camera);

        // center red square
        mRedSq->draw(*camera);

        // corner squares
        mTLSq->draw(*camera);
        mTRSq->draw(*camera);
        mBRSq->draw(*camera);
        mBLSq->draw(*camera);
    }

    void cleanup() {}

private:
    std::shared_ptr<Engine> engine;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Renderable> mBlueSq;
    std::shared_ptr<Renderable> mRedSq;
    std::shared_ptr<Renderable> mTLSq;
    std::shared_ptr<Renderable> mTRSq;
    std::shared_ptr<Renderable> mBRSq;
    std::shared_ptr<Renderable> mBLSq;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    MyGame scene;
    Mn::RunStatic<MyGame>(scene, window);
    return 0;
}
