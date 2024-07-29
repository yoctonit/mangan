#include "InvertEffect.h"

InvertEffect::InvertEffect() : Material(
        "shader/Effect.vert",
        "shader/InvertEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
}
