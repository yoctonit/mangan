#include "engine/Window.h"
#include "src/Core.h"
#include "src/Loop.h"
#include "game/MyGame.h"


int main() {
    Mn::Window wnd(640, 480, "Example 2.6");
    Loop loop(wnd);

    Core engine;
    engine.init();

    auto myGame = std::make_shared<MyGame>(engine, loop);
    myGame->start();

    return 0;
}
