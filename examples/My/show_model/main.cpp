//
// Created by ivan on 30.4.2020..
//

#include "core/window/gl_window.h"
#include "model_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(1024, 1024, "Show Model", 4, 6)) {
        window.clean_up();
        return 1;
    }

    model_scene s(window.width(), window.height());

    window.set_scene(&s);
    window.action();

    return 0;
}
