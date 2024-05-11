#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_05_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_05_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <core/Shader.h>
#include <core/VAO.h>
#include <core/VBO.h>
#include <geometry/Triangle.h>
#include <geometry/Square.h>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        shader = std::make_shared<Mn::ShaderProgram>("shader/position.vs", "shader/position.fs");

        bufferTriangle = std::make_shared<Mn::VBO>(Mn::geometry::equilateral_triangle(1.5f));
        bufferSquare = std::make_shared<Mn::VBO>(Mn::geometry::square(1.0f));

        vaoTriangle = std::make_shared<Mn::VAO>();
        vaoTriangle->connect(*bufferTriangle, *shader, "a_position", 3, 0, nullptr);
        vaoSquare = std::make_shared<Mn::VAO>();
        vaoSquare->connect(*bufferSquare, *shader, "a_position", 3, 0, nullptr);
    }

    static void clear() {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        clear();

        shader->use();
        vaoTriangle->activate();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        vaoSquare->activate();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
    std::shared_ptr<Mn::ShaderProgram> shader;
    std::shared_ptr<Mn::VAO> vaoTriangle;
    std::shared_ptr<Mn::VAO> vaoSquare;
    std::shared_ptr<Mn::VBO> bufferTriangle;
    std::shared_ptr<Mn::VBO> bufferSquare;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_05_H
