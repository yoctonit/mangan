#include "Run.h"
#include "byo2dge/Engine.h"
#include "byo2dge/SceneFileParser.h"
#include "byo2dge/Renderable.h"

class MyGame {
public:
    void initialize(int, int) {
        engine = std::make_shared<Engine>();
        SceneFileParser sceneParser("assets/scene.json");

        camera = sceneParser.parseCamera();
        mSqSet = sceneParser.parseSquares(
                engine->shaderResources()->getConstColorShader(),
                engine->vertexBuffer()->get());
    }

    void draw() const {
        Engine::clearCanvas(0.9f, 0.9f, 0.9f, 1.0f);
        camera->setViewAndCameraMatrix();
        for (auto &sq: mSqSet)
            sq->draw(*camera);
    }

    void update(const Mn::Input &input, double) {
        // Simple game: move the white square and pulse the red
        std::shared_ptr<Transform> whiteXform = mSqSet[0]->getXform();
        float deltaX = 0.05;

        // Step A: Rotate the white square
        if (input.is_pressed(Mn::key::right)) {
            if (whiteXform->getXPos() > 30.0f) // the right-bound of the window
                whiteXform->setPosition(10.0f, 60.0f);
            whiteXform->incXPosBy(deltaX);
        }
        if (input.is_clicked(Mn::key::up)) {
            whiteXform->incRotationByDegree(1);
        }
        // Step B: pulse the red square
        std::shared_ptr<Transform> redXform = mSqSet[1]->getXform();
        if (input.is_pressed(Mn::key::down)) {
            if (redXform->getWidth() > 5.0f)
                redXform->setSize(2.0f, 2.0f);
            redXform->incSizeBy(0.05f);
        }
    }

    void cleanup() {}

private:
    std::shared_ptr<Engine> engine;
    std::shared_ptr<Camera> camera;
    std::vector<std::shared_ptr<Renderable>> mSqSet;
};

int main() {
    Mn::Window window(640, 480, "ExampleScene");
    MyGame scene;
    Mn::Run<MyGame>(scene, window);
    return 0;
}
