#ifndef OPENGL_EXAMPLES_EXAMPLE_SCENE_13_H
#define OPENGL_EXAMPLES_EXAMPLE_SCENE_13_H

#include <iostream>
#include <memory>
#include <wnd/Input.h>
#include <camera/Camera2D.h>
#include <renderable/Axes2D.h>
#include <builder/RenderableBuilder.h>

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

        // objects
        axes = std::make_shared<Mn::renderable::Axes2D>(-20, 20, -20, 20, 1);

        Mn::builder::RenderableBuilder builder;
        hero = builder
                .make_sprite("image/minion_sprite.png")
                .pixel_positions(0.0f, 120.0f, 0.0f, 180.0f)
                .position(-5.0f, -2.0f)
                .size(2.0f, 3.0f)
                .create();

        portal = builder
                .make_sprite("image/minion_sprite.png")
                .pixel_positions(130.0f, 310.0f, 0.0f, 180.0f)
                .position(5.0f, 3.0f)
                .size(3.0f, 3.0f)
                .create();

        dye_pack = builder
                .make_sprite("image/minion_sprite.png")
                .pixel_positions(510.0f, 595.0f, 23.0f, 153.0f)
                .size(0.8f, 1.3f)
                .create();

        // config
        // Allows transparency with textures.
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    }

    void draw() {
        camera->set_view_and_camera_matrix();
        camera->clear_background();

        axes->draw(glm::mat4{1.0f}, camera->matrix());
        dye_pack->draw(camera->matrix());
        portal->draw(camera->matrix());
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
    std::shared_ptr<Mn::renderable::Sprite> hero;
    std::shared_ptr<Mn::renderable::Sprite> portal;
    std::shared_ptr<Mn::renderable::Sprite> dye_pack;
};

#endif //OPENGL_EXAMPLES_EXAMPLE_SCENE_13_H
