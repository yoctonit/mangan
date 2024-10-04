#include "src/Core.h"
#include "game/MyGame.h"


int main() {
    Core engine(640, 480, "Example 5.3");

    MyGame game(engine);
    engine.start(game);

    return 0;
}
