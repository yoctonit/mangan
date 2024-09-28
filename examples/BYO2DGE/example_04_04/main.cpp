#include "engine/Window.h"
#include "src/Core.h"
#include "src/Loop.h"
#include "game/MyGame.h"


int main() {
    Mn::Window wnd(640, 480, "Example 2.6");

    // Initialize the game engine
    Core engine;
    engine.init();

    MyGame myGame(engine);

    Loop loop;
    loop.start(&myGame, wnd);

    return 0;
}
