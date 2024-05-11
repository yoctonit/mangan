#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <camera/Camera2D.h>
#include <renderable/Axes2D.h>
#include <renderable/Textured.h>
#include <renderable/Sprite.h>
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

        auto background_texture = std::make_shared<Mn::Texture>("image/bg.png");
        auto minion_texture = std::make_shared<Mn::Texture>("image/minion_portal.png");
        auto sprite_texture = std::make_shared<Mn::Texture>("image/minion_sprite.png");

        auto textured_square_buffer = std::make_shared<Mn::VBO>(Mn::geometry::textured_square(1.0f));
        auto conn1 = std::make_shared<Mn::connection::Textured>(shader, textured_square_buffer);

        auto square_geometry_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square(1.0f));
        auto square_texture_coord_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square_uv(), GL_DYNAMIC_DRAW);
        auto conn2 = std::make_shared<Mn::connection::Sprite>(
                shader, square_geometry_buffer, square_texture_coord_buffer);

        // objects
        axes = std::make_shared<Mn::renderable::Axes2D>(-20, 20, -20, 20, 1);

        background = std::make_shared<Mn::renderable::Textured>(
                conn1,
                background_texture,
                GL_TRIANGLE_STRIP, 0, 4
        );
        background->transform()->size(15.0f, 15.0f);

        minion = std::make_shared<Mn::renderable::Textured>(
                conn1,
                minion_texture,
                GL_TRIANGLE_STRIP, 0, 4
        );
        minion->transform()->position(5.0f, 3.0f);
        minion->transform()->size(2.0f, 2.0f);

        Mn::geometry::square_sprite ss(sprite_texture->width(), sprite_texture->height());
        ss.element_pixel_positions(0.0f, 120.0f, 0.0f, 180.0f);
        hero = std::make_shared<Mn::renderable::Sprite>(
                conn2,
                sprite_texture,
                ss.element_uv_coordinates(),
                GL_TRIANGLE_STRIP, 0, 4
        );
        hero->transform()->position(-5.0f, -2.0f);
        hero->transform()->size(2.0f, 3.0f);

        /*
         * Builder builder;
         * hero = builder
         *   .square_sprite("minion_sprite.png")
         *   .pixel_positions(0.0f, 120.0f, 0.0f, 180.0f)
         *   .position(-5.0f, -2.0f)
         *   .size(2.0f, 3.0f)
         *   .create();
         */

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
        hero->draw(camera->matrix());
    }

    void update(const Mn::Input &input) {
        if (input.is_clicked(Mn::input::mouse::button::left)) {
            glm::vec2 wc = camera->mouse_wc(input);
            std::cout << "(" << wc.x << ", " << wc.y << ")\n";
        }
        float delta = 0.05f;
        if (input.is_pressed(Mn::input::key::left)) {
            hero->transform()->inc_x_position_by(-delta);
        } else if (input.is_pressed(Mn::input::key::right)) {
            hero->transform()->inc_x_position_by(delta);
        }
        if (input.is_pressed(Mn::input::key::up)) {
            hero->transform()->inc_y_position_by(delta);
        } else if (input.is_pressed(Mn::input::key::down)) {
            hero->transform()->inc_y_position_by(-delta);
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
    std::shared_ptr<Mn::renderable::Sprite> hero;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_11_H
