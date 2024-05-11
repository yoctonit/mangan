#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H

#include <iostream>
#include <memory>
#include <core/Shader.h>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "Initializing scene\n";
        shader = std::make_shared<Mn::ShaderProgram>("shader/simple.vs", "shader/simple.fs");
    }

    void draw() {
    }

    [[nodiscard]] bool end() const {
        return _should_end;
    }

    void update(const Mn::Input &input) {
        if (input.is_clicked(Mn::input::key::q)) {
            _should_end = true;
        }
    }

    ~ExampleScene() {
        std::cout << "~ExampleScene()\n";
    }
private:
    std::shared_ptr<Mn::ShaderProgram> shader;
    bool _should_end{};
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H
