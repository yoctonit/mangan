//
// Created by ivan on 28.4.2020..
//

#include "gl_window.h"
#include "program_library.h"


int main()
{
    mn::gl_window& window = mn::gl_window::instance();

    if (!window.create(640, 640, "Triangle", 4, 6)) {
        window.clean_up();
        return 1;
    }

    mn::program_library& lib = mn::program_library::instance();
    mn::shader_program& program = lib.get_program(
            "basic.vert", "basic.frag");

    program.print();

    return 0;
}
