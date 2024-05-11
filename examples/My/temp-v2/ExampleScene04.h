#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_04_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_04_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include "core/Shader.h"
#include "core/VAO.h"
#include "core/VBO.h"
#include "geometry/Triangle.h"

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        shader = std::make_shared<Mn::ShaderProgram>("shader/position.vs", "shader/position.fs");

        buffer = std::make_shared<Mn::VBO>(Mn::geometry::equilateral_triangle(1.0f));

        vao = std::make_shared<Mn::VAO>();
        vao->connect(*buffer, *shader, "a_position", 3, 0, nullptr);
    }

    static void clear() {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void draw() {
        clear();

        shader->use();
        vao->activate();
        glDrawArrays(GL_TRIANGLES, 0, 3);
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
    std::shared_ptr<Mn::VAO> vao;
    std::shared_ptr<Mn::VBO> buffer;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_04_H
