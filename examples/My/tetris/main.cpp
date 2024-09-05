//
// Created by ivan on 9.5.2020..
//

//#include "core/window/gl_window.h"
//
//int main() {
//    mn::gl_window& window = mn::gl_window::instance();
//
//    if (!window.create(600, 600, "Tetris", 4, 6)) {
//        window.clean_up();
//        return 1;
//    }
//
//    // window.action_test();
//    window.action();
//
//    return 0;
//}

#include "game_grid.h"
#include "tetronimo.h"

int main() {

    game_grid grid;
    grid.display();

    tetronimo_bar_left t;
    t.display();

    return 0;
}
