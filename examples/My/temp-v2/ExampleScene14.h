#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_14_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_14_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <camera/Camera2D.h>
#include <renderable/Axes2D.h>
#include <renderable/AnimatedSprite.h>

class ExampleScene {
public:
    void initialize(int w, int h) {
        std::cout << "\nInitializing Scene\n";
        std::cout << "==================\n";

        camera = std::make_shared<Mn::Camera2D>(
                glm::vec2{0.0f, 0.0f}, 12.0f,
                0, 0, w, h
        );
        camera->setup_viewport();

        // objects
        axes = std::make_shared<Mn::renderable::Axes2D>(-10, 10, -10, 10, 1);

        auto texture_shader = std::make_shared<Mn::Shader::Texture>();
        auto square_geometry_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square());
        auto square_texture_coord_buffer = std::make_shared<Mn::VBO>(Mn::geometry::square_uv(), GL_DYNAMIC_DRAW);
        auto sprite_connection = std::make_shared<Mn::connection::Sprite>(
                texture_shader,
                square_geometry_buffer,
                square_texture_coord_buffer
        );
        auto sprite_texture = std::make_shared<Mn::Texture>("image/minion_sprite.png");

        hero = std::make_shared<Mn::renderable::AnimatedSprite>(
                sprite_connection,
                sprite_texture,
                GL_TRIANGLE_STRIP, 0, 4
        );
        hero->sprite_sequence(512.0f, 0.0f, 204.0f, 164.0f,0.0f, 5);

        // config
        // Allows transparency with textures.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    void draw() {
        camera->set_view_and_camera_matrix();
        camera->clear_background();

        axes->draw(glm::mat4{1.0f}, camera->matrix());
        hero->draw(camera->matrix());
    }

    void update(const Mn::Input &input) {
        hero->update_animation();
        float delta = 0.05f;
        if (input.is_pressed(Mn::input::key::left)) {
            hero->transform()->inc_x_position_by(-delta);
        } else if (input.is_pressed(Mn::input::key::right)) {
            hero->transform()->inc_x_position_by(delta);
        }

        if (input.is_clicked(Mn::input::key::a)) {
            Mn::renderable::AnimationType t = hero->animation_type();
            if (t == Mn::renderable::AnimationType::right) {
                std::cout << "right -> left\n";
                t = Mn::renderable::AnimationType::left;
            } else if (t == Mn::renderable::AnimationType::left) {
                std::cout << "left -> swing\n";
                t = Mn::renderable::AnimationType::swing;
            } else {
                std::cout << "swing -> right\n";
                t = Mn::renderable::AnimationType::right;
            }
            hero->animation_type(t);
        }

        if (input.is_clicked(Mn::input::key::up)) {
            hero->inc_animation_speed(1);
        } else if (input.is_clicked(Mn::input::key::down)) {
            hero->inc_animation_speed(-1);
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
    std::shared_ptr<Mn::renderable::AnimatedSprite> hero;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_14_H
