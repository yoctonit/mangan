#include "AdditiveBlendEffect.h"

AdditiveBlendEffect::AdditiveBlendEffect(
        const Texture &blendTexture,
        float originalStrength,
        float blendStrength)
        : Material(
        "shader/Effect.vert",
        "shader/AdditiveBlendEffect.frag"
) {
    // the actual texture reference is not 0;
    // will be set from render target by postprocessor class
    addUniform("tex", 0, 1);
    addUniform("blendTexture", blendTexture.textureRef(), 2);
    addUniform("originalStrength", originalStrength);
    addUniform("blendStrength", blendStrength);
}
