#include "TintEffect.h"

TintEffect::TintEffect(glm::vec3 tintColor) : Material(
        "shader/Effect.vert",
        "shader/TintEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("tintColor", tintColor);
}
