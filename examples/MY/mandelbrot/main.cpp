//
// Created by ivan on 23.4.2020..
//

#include "core/window/gl_window.h"
#include "mandelbrot_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(900, 600, "Mandelbrot", 4, 6, 60)) {
        window.clean_up();
        return 1;
    }

    mandelbrot_scene m(window.width(), window.height());

    window.set_scene(&m);
    window.action();

    return 0;
}
