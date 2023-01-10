//
// Created by ivan on 27.4.2020..
//

#include "core/window/gl_window.h"
#include "colored_square_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(640, 640, "Colored Square", 4, 6)) {
        window.clean_up();
        return 1;
    }

    colored_square_scene cs(window.width(), window.height());

    window.set_scene(&cs);
    window.action();

    return 0;
}
