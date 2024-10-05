#include "src/Core.h"
#include "game/MyGame.h"


int main() {
    Core engine(640, 480, "Example 5.3");
    engine.addFont("consolas-16");
    engine.addFont("consolas-24");
    engine.addFont("consolas-32");
    engine.addFont("consolas-72");
    engine.addFont("segment7-96");
    engine.addFont("system_default_font");

    MyGame game(engine);
    engine.start(game);

    return 0;
}
