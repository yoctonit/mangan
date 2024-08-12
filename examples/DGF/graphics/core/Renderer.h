#ifndef DGF_GRAPHICS_CORE_RENDERER_H
#define DGF_GRAPHICS_CORE_RENDERER_H

#include <glm/vec3.hpp>
#include "Scene.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "../light/Light.h"
#include "../light/Shadow.h"

class Renderer {
public:
    Renderer();

    void setClearColor(glm::vec3 color);

    void setClearColor(float r, float g, float b, float a = 1.0f);

    void setDimensions(int w, int h);

    void render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera);

    void enableShadows(const std::shared_ptr<DirectionalLight> &shadowLight, float strength, glm::vec2 resolution,
                       float bias);

    void enableShadows(const std::shared_ptr<DirectionalLight> &shadowLight);

    glm::vec4 clearColor;
    bool clearColorBuffer;
    bool clearDepthBuffer;

    int width;
    int height;

    std::shared_ptr<RenderTarget> renderTarget;

    std::shared_ptr<Light> light0{nullptr};
    std::shared_ptr<Light> light1{nullptr};
    std::shared_ptr<Light> light2{nullptr};
    std::shared_ptr<Light> light3{nullptr};

    bool shadowsEnabled{};
    std::shared_ptr<Shadow> shadowObject{nullptr};
};

#endif //DGF_GRAPHICS_CORE_RENDERER_H
