#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_10_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_10_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <camera/Camera2D.h>
#include <object/Square.h>
#include <renderable/Axes2D.h>

class ExampleScene {
public:
    void initialize(int w, int h) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        camera = std::make_shared<Mn::Camera2D>(
                glm::vec2{0.0f, 0.0f}, 22.0f,
                0, 0, w, h
        );
        camera->setup_viewport();

        // common renderable for square objects
        auto square_renderable = std::make_shared<Mn::renderable::SolidColorSquare>(1.0f);

        square1 = std::make_shared<Mn::object::SolidColorSquare>(square_renderable);
        square1->set_color(1.0f, 0.0f, 0.0f);
        square1->transform()->position(3.0f, 4.0f);
        square1->transform()->size(2.0f, 3.0f);

        square2 = std::make_shared<Mn::object::SolidColorSquare>(square_renderable);
        square2->set_color(0.0f, 1.0f, 0.0f);
        square2->transform()->position(-3.0f, -1.0f);
        square2->transform()->size(4.0f, 1.0f);

        axes = std::make_shared<Mn::renderable::Axes2D>(-10, 10, -10, 10, 1);
    }

    void draw() {
        camera->set_view_and_camera_matrix();

        camera->clear_background();
        axes->draw(glm::mat4{1.0f}, camera->camera_matrix());
        square1->draw(camera);
        square2->draw(camera);
    }

    void update(const Mn::Input &input) {
        if (input.is_clicked(Mn::input::mouse::button::left)) {
            glm::vec2 wc = camera->mouse_wc(input);
            std::cout << "(" << wc.x << ", " << wc.y << ")\n";
        }
    }

    [[nodiscard]] static bool end() {
        return false;
    }

    ~ExampleScene() {
        std::cout << "\nCleanup Scene\n";
        std::cout << "=============\n";
    }

private:
    std::shared_ptr<Mn::Camera2D> camera;
    std::shared_ptr<Mn::object::SolidColorSquare> square1;
    std::shared_ptr<Mn::object::SolidColorSquare> square2;
    std::shared_ptr<Mn::renderable::Axes2D> axes;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_10_H
