#include "VerticalBlurEffect.h"

VerticalBlurEffect::VerticalBlurEffect(glm::vec2 textureSize, int blurRadius)
        : Material(
        "shader/Effect.vert",
        "shader/VerticalBlurEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("textureSize", textureSize);
    addUniform("blurRadius", blurRadius);
}
