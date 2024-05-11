#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_09_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_09_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <renderable/Triangle.h>
#include <renderable/Axes2D.h>
#include <camera/Camera2D.h>

class ExampleScene {
public:
    void initialize(int w, int h) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        camera = std::make_shared<Mn::Camera2D>(
                glm::vec2{0.0f, 0.0f}, 40.0f,
                0, 0, w, h
        );
        // camera->set_wc_center(.5f, .5f);
        // camera->set_background_color(1.0f, 1.0f, 1.0f);

        triangle = std::make_shared<Mn::renderable::Triangle>(2.0f);
        triangle->set_color(1.0f, 1.0f, 0.0f);
        axes = std::make_shared<Mn::renderable::Axes2D>(-15, 15, -15, 15, 3);
    }

    void draw() {
        camera->set_view_and_camera_matrix();

        axes->draw(glm::mat4{1.0f}, camera->camera_matrix());
        triangle->draw(glm::mat4{1.0f}, camera->camera_matrix());
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
    std::shared_ptr<Mn::Camera2D> camera;
    std::shared_ptr<Mn::renderable::Triangle> triangle;
    std::shared_ptr<Mn::renderable::Axes2D> axes;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_09_H
