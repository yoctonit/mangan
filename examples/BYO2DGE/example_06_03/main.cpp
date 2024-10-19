#include "src/Core.h"
#include "game/MyGame.h"


int main() {
    Core engine(640, 480, "Example 6.2");
    engine.addFont("system_default_font");

    MyGame game(engine);
    engine.start(game);

    return 0;
}
