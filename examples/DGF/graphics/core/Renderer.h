#ifndef DGF_GRAPHICS_CORE_RENDERER_H
#define DGF_GRAPHICS_CORE_RENDERER_H

#include <glm/vec3.hpp>
#include "Scene.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "../light/Light.h"

class Renderer {
public:
    Renderer();

    static void setClearColor(glm::vec3 color);

    static void setClearColor(float r, float g, float b, float a = 1.0f);

    void setDimensions(int w, int h);

    void render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera);

    // static void render1(const std::shared_ptr<Object3D> &object, const std::shared_ptr<Camera>& camera);

    bool clearColorBuffer;
    bool clearDepthBuffer;

    int width;
    int height;

    std::shared_ptr<RenderTarget> renderTarget;

    std::shared_ptr<Light> light0{nullptr};
    std::shared_ptr<Light> light1{nullptr};
    std::shared_ptr<Light> light2{nullptr};
    std::shared_ptr<Light> light3{nullptr};
};

#endif //DGF_GRAPHICS_CORE_RENDERER_H
