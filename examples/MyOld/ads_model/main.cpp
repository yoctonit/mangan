//
// Created by ivan on 04.5.2020..
//

#include "core/window/gl_window.h"
#include "ads_scene.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(1024, 1024, "ADS Model", 4, 6)) {
        window.clean_up();
        return 1;
    }

    ads_scene ads(window.width(), window.height());

    window.set_scene(&ads);
    window.action();

    return 0;
}
