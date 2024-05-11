#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_07_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_07_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <renderable/Triangle.h>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        triangle = std::make_shared<Mn::renderable::SolidColorTriangle>(0.1f, 0.1f, 0.6f);
    }

    static void clear() {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        clear();

        triangle->draw();
    }

    void update(const Mn::Input &) {}

    [[nodiscard]] static bool end() {
        return false;
    }

    ~ExampleScene() {
        std::cout << "\nCleanup Scene\n";
        std::cout << "=============\n";
    }

private:
    std::shared_ptr<Mn::renderable::SolidColorTriangle> triangle;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_07_H
