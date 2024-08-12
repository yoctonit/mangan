#ifndef DGF_GRAPHICS_LIGHT_SHADOW_H
#define DGF_GRAPHICS_LIGHT_SHADOW_H

#include <string>
#include <map>
#include <memory>
#include <glm/vec3.hpp>
#include "../core/Uniform.h"
#include "../core/Camera.h"
#include "../core/RenderTarget.h"
//#include "../material/DepthMaterial.h"
#include "DirectionalLight.h"
class DepthMaterial;

class Shadow {
public:
    std::shared_ptr<DirectionalLight> lightSource;

    // camera used to render scene from perspective of light
    std::shared_ptr<Camera> camera;

    // target used during the shadow pass, contains depth texture
    std::shared_ptr<RenderTarget> renderTarget;

    // render only depth data to target texture
    std::shared_ptr<DepthMaterial> material;

    // controls darkness of shadow
    float strength;

    // used to avoid visual artifacts due to rounding/sampling precision issues
    float bias;

    // constructor
    Shadow(std::shared_ptr<DirectionalLight> ls, float s, glm::vec2 resolution, float b);

    explicit Shadow(std::shared_ptr<DirectionalLight> lightSource);

    void setCameraBounds(
            float left, float right,
            float bottom, float top,
            float near, float far);

    void updateInternal();

//    [[nodiscard]] std::map<std::string, Uniform> &uniforms();

//protected:
//    // Store Uniform objects, indexed by name of associated variable in shader.
//    std::map<std::string, Uniform> m_uniforms;
};

#endif //DGF_GRAPHICS_LIGHT_SHADOW_H
