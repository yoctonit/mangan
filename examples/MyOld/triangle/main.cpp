//
// Created by ivan on 19.4.2020..
//

#include "core/window/gl_window.h"
#include "triangle_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(640, 640, "Triangle", 4, 6)) {
        window.clean_up();
        return 1;
    }

    triangle_scene t(window.width(), window.height());

    window.set_scene(&t);
    window.action();

    return 0;
}
