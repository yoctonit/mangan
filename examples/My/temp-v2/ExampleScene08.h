#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_08_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_08_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <renderable/Triangle.h>
#include <renderable/Square.h>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        triangle = std::make_shared<Mn::renderable::SolidColorTriangle>(0.5f);
        square = std::make_shared<Mn::renderable::SolidColorSquare>(1.0f);
    }

    static void clear() {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        clear();

        square->draw(0.5f, 0.1f, 0.0f);
        triangle->draw(0.1f, 0.1f, 0.6f);
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
    std::shared_ptr<Mn::renderable::SolidColorSquare> square;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_08_H
