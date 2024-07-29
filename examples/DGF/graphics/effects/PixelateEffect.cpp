#include "PixelateEffect.h"

PixelateEffect::PixelateEffect(float pixelSize, glm::vec2 resolution) : Material(
        "shader/Effect.vert",
        "shader/PixelateEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("pixelSize", pixelSize);
    addUniform("resolution", resolution);
}
