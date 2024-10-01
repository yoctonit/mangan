#include "src/Core.h"
#include "game/MyGame.h"


int main() {
    Core engine(640, 480, "Example 4.5");

    LevelManager game;
    game.setLevel(std::make_shared<MyGame>(engine, game));

    engine.start(game);

    return 0;
}
