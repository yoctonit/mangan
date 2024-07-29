#ifndef DGF_GRAPHICS_EXTRAS_POSTPROCESSOR_H
#define DGF_GRAPHICS_EXTRAS_POSTPROCESSOR_H

#include <vector>
#include <memory>

#include "../core/Renderer.h"
#include "../core/RenderTarget.h"
#include "../core/Scene.h"
#include "../core/Camera.h"
#include "../geometry/Geometry.h"
#include "../material/Material.h"

class Postprocessor {
public:
    std::shared_ptr<Renderer> renderer;
    std::vector<std::shared_ptr<Object3D>> sceneList;
    std::vector<std::shared_ptr<Camera>> cameraList;
    std::vector<std::shared_ptr<RenderTarget>> renderTargetList;
    std::shared_ptr<RenderTarget> finalRenderTarget;

    Postprocessor(
            std::shared_ptr<Renderer> r,
            const std::shared_ptr<Object3D>& s,
            const std::shared_ptr<Camera>& c,
            const std::shared_ptr<RenderTarget>& rt);

    void addEffect(const std::shared_ptr<Material> &effect);

    void render();

private:
    // reusable elements for added effects
    std::shared_ptr<Camera> m_orthoCamera;
    std::shared_ptr<Geometry> m_rectangleGeom;
};

#endif //DGF_GRAPHICS_EXTRAS_POSTPROCESSOR_H
