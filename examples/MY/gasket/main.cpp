//
// Created by ivan on 26.4.2020..
//

#include "core/window/gl_window.h"
#include "gasket_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(640, 640, "Gasket", 4, 6)) {
        window.clean_up();
        return 1;
    }

    gasket_scene g(window.width(), window.height());

    window.set_scene(&g);
    window.action();

    return 0;
}
