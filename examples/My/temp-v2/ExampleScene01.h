#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H

#include <iostream>

class ExampleScene {
public:
    void initialize(int, int) {
        std::cout << "Initializing scene\n";
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << "\n";
    }

    void draw() {
    }

    [[nodiscard]] bool end() const {
        return _should_end;
    }

    void update(const Mn::Input &input) {
        if (input.is_clicked(Mn::input::mouse::button::left)) {
            std::cout << "Left mouse clicked at " << "("
                      << input.mouse_x_position() << ", "
                      << input.mouse_y_position() << ")\n";
        }
        if (input.is_clicked(Mn::input::key::q)) {
            _should_end = true;
        }
    }

    ~ExampleScene() {
        std::cout << "~ExampleScene()\n";
    }
private:
    bool _should_end{};
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_01_H
