#include "Effect.h"

Effect::Effect() : Material(
        "shader/Effect.vert",
        "shader/Effect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
}
