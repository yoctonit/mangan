#include "VignetteEffect.h"

VignetteEffect::VignetteEffect(float dimStart, float dimEnd, glm::vec3 dimColor) : Material(
        "shader/Effect.vert",
        "shader/VignetteEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("dimStart", dimStart);
    addUniform("dimEnd", dimEnd);
    addUniform("dimColor", dimColor);
}
