//
// Created by ivan on 16.5.2020..
//

#include "core/window/gl_window.h"
#include "plane_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(800, 800, "Spaceship", 4, 6)) {
        window.clean_up();
        return 1;
    }

    plane_scene plane(window.width(), window.height());

    window.set_scene(&plane);
    window.action();

    return 0;
}
