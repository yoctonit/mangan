#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <camera/Camera2D.h>
#include <renderable/Axes2D.h>
#include <renderable/Textured.h>
#include <geometry/Square.h>

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

        // assets
        auto shader = std::make_shared<Mn::Shader::Texture>();
        auto textured_square_buffer = std::make_shared<Mn::VBO>(Mn::geometry::textured_square(1.0f));
        auto conn = std::make_shared<Mn::connection::Textured>(shader, textured_square_buffer);
        auto background_texture = std::make_shared<Mn::Texture>("image/bg.png");
        auto minion_texture = std::make_shared<Mn::Texture>("image/minion_portal.png");

        // objects
        axes = std::make_shared<Mn::renderable::Axes2D>(-20, 20, -20, 20, 1);

        background = std::make_shared<Mn::renderable::Textured>(
                conn,
                background_texture,
                GL_TRIANGLE_STRIP, 0, 4
        );
        background->transform()->size(15.0f, 15.0f);
        
        minion = std::make_shared<Mn::renderable::Textured>(
                conn,
                minion_texture,
                GL_TRIANGLE_STRIP, 0, 4
        );
        minion->transform()->position(5.0f, 3.0f);
        minion->transform()->size(2.0f, 2.0f);

        // config
        // Allows transparency with textures.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    void draw() {
        camera->set_view_and_camera_matrix();

        camera->clear_background();

        background->draw(camera->matrix());
        axes->draw(glm::mat4{1.0f}, camera->matrix());
        minion->draw(camera->matrix());
    }

    void update(const Mn::Input &input) {
        if (input.is_clicked(Mn::input::mouse::button::left)) {
            glm::vec2 wc = camera->mouse_wc(input);
            std::cout << "(" << wc.x << ", " << wc.y << ")\n";
        }
        float delta = 0.05f;
        if (input.is_pressed(Mn::input::key::left)) {
            minion->transform()->inc_x_position_by(-delta);
        } else if (input.is_pressed(Mn::input::key::right)) {
            minion->transform()->inc_x_position_by(delta);
        }
        if (input.is_pressed(Mn::input::key::up)) {
            minion->transform()->inc_y_position_by(delta);
        } else if (input.is_pressed(Mn::input::key::down)) {
            minion->transform()->inc_y_position_by(-delta);
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
    std::shared_ptr<Mn::renderable::Axes2D> axes;
    std::shared_ptr<Mn::renderable::Textured> background;
    std::shared_ptr<Mn::renderable::Textured> minion;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H
