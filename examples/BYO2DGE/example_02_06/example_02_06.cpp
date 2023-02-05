#include "Run.h"
#include "byo2dge/SimpleShader.h"
#include "byo2dge/Square.h"

class Core {
public:
    void initialize(int, int) {
        mGLVertexBuffer = std::make_shared<Square>();
        mShader = std::make_shared<SimpleShader>("shader/simple.vs", "shader/simple.fs");
        glClearColor(0.0f, 0.8f, 0.0f, 1.0f);
    }

    void draw() {
        glClear(GL_COLOR_BUFFER_BIT);

        // Step A: Activate the shader
        mShader->activate(mGLVertexBuffer->get(), mColor);

        // Step B: Draw with the currently activated geometry and the activated shader
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }

    void cleanup() {}

    void Color(glm::vec4 c) { mColor = c; }

private:
    std::shared_ptr<SimpleShader> mShader{};
    std::shared_ptr<Square> mGLVertexBuffer{};
    glm::vec4 mColor{};
};

int main() {
    Mn::Window window(800, 600, "ExampleScene");
    Core scene;
    scene.Color(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    Mn::RunStatic<Core>(scene, window);
    return 0;
}
