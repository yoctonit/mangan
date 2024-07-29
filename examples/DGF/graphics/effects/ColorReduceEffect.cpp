#include "ColorReduceEffect.h"

ColorReduceEffect::ColorReduceEffect(float levels) : Material(
        "shader/Effect.vert",
        "shader/ColorReduceEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("levels", levels);
}
