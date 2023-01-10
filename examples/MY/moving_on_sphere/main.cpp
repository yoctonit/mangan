//
// Created by ivan on 21.5.2020..
//

#include "core/window/gl_window.h"
#include "sphere_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(800, 800, "Spaceship", 4, 6)) {
        window.clean_up();
        return 1;
    }

    sphere_scene sphere(window.width(), window.height());

    window.set_scene(&sphere);
    window.action();

    return 0;
}
