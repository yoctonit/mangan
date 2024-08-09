#include "BrightFilterEffect.h"

BrightFilterEffect::BrightFilterEffect(float threshold) : Material(
        "shader/Effect.vert",
        "shader/BrightFilterEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("threshold", threshold);
}
