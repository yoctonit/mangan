#include <glad/glad.h>
#include <iostream>

#include "Run.h"

/*
class Example01 {
public:
    Example01() : r(.5f), g(.3f), b(.5f), a(1.0f) {
        std::cout << "Construct Example01 scene.\n";
    }

    void Render() {
        if (shouldRender) {
            std::cout << "Render scene with background color (" << r << ", " << g << ", " << b << ", " << a << ")\n";
            std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
            std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";
            shouldRender = false;
        }
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

private:
    float r, g, b, a;
    bool shouldRender = true;
};

int main() {
    Mn::Window wnd(800, 600, "Example01");
    Mn::ShowStaticScene<Example01>(wnd);
    return 0;
}
*/

class Example02 {
public:
    Example02() : r(.5f), g(.3f), b(.5f), a(1.0f) {
        std::cout << "Construct Example02 scene.\n";
        glClearColor(r, g, b, a);
    }

    void Update(const Mn::Input &input) {
        if (input.IsClickedKey(MN_KEY_ESCAPE)) {
            running = false;
        }
        if (input.IsClickedKey(MN_KEY_R)) {
            r += 0.1f;
            if (r > 1.0f) r = 0.0f;
        }
        if (input.IsClickedKey(MN_KEY_G)) {
            g += 0.1f;
            if (g > 1.0f) g = 0.0f;
        }
        if (input.IsClickedKey(MN_KEY_B)) {
            b += 0.1f;
            if (b > 1.0f) b = 0.0f;
        }
        if (input.IsClickedKey(MN_KEY_A)) {
            a += 0.1f;
            if (a > 1.0f) a = 0.0f;
        }
    }

    void Render() const {
        static bool shouldRender = true;

        if (shouldRender) {
            std::cout << "Render scene with background color (" << r << ", " << g << ", " << b << ", " << a << ")\n";
            std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
            std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";

            shouldRender = false;
        }
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    [[nodiscard]] bool IsRunning() const {
        return running;
    }

private:
    float r, g, b, a;
    bool running = true;
};

int main() {
    Mn::Window wnd(640, 320, "Example01");
    Mn::ShowScene<Example02>(wnd);
    return 0;
}

/*
class Example03 : public Mn::Scene {
public:
    Example03() : Mn::Scene(), r(.5f), g(.3f), b(.5f), a(1.0f) {
        std::cout << "Construct Example03 scene.\n";
        glClearColor(r, g, b, a);

        registerAction(MN_KEY_W, "UP");
        registerAction(MN_KEY_S, "DOWN");
        registerAction(MN_KEY_A, "LEFT");
        registerAction(MN_KEY_D, "RIGHT");
        registerAction(MN_KEY_ESCAPE, "QUIT");
    }

    void sDoAction(const Mn::Action &action) override {
        if (action.type() == "START") {
            if (action.name() == "UP") {
                std::cout << "UP action START called\n";
                shouldRender = true;
            } else if (action.name() == "DOWN") {
                std::cout << "DOWN action called\n";
            } else if (action.name() == "LEFT") {
                std::cout << "LEFT action called\n";
            } else if (action.name() == "RIGHT") {
                std::cout << "RIGHT action called\n";
            } else if (action.name() == "QUIT") {
                std::cout << "QUIT action called\n";
                m_isRunning = false;
            }
        }

        if (action.type() == "END") {
            if (action.name() == "UP") {
                std::cout << "UP action END called\n";
                shouldRender = false;
            }
        }
    }

    void Update() override {
    }

    void Render() const override {
        if (shouldRender) {
            std::cout << "Render scene with background color (" << r << ", " << g << ", " << b << ", " << a << ")\n";
            std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
            std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
            std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";
        }
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

private:
    float r, g, b, a;
    bool shouldRender = false;
};

// int main() {
    // Mn::Engine engine(Mn::Engine::Config(640, 320, "Test 13"));
    // engine.SetWindowTitle("Test 1").Create();
    // auto scene = std::make_shared<Example01>(&engine);
    // engine.SetScene(std::make_shared<Example01>(&engine));

    // engine.Run();
    // engine.ShowStaticScene<Example01>();

    // Example01 example01;
    // engine.ShowStaticScene<>(example01);

    // engine.ShowScene<Example02>();

    // engine.SetScene(std::make_shared<Example03>()).Run();
    // return 0;
// }
*/
