#ifndef DGF_GRAPHICS_CORE_RENDERER_H
#define DGF_GRAPHICS_CORE_RENDERER_H

#include <glm/vec3.hpp>
#include "Scene.h"
#include "Camera.h"

class Renderer {
public:
    static void initialize();

    static void setClearColor(glm::vec3 color);

    static void setClearColor(float r, float g, float b, float a = 1.0f);

    static void render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera);

    // static void render1(const std::shared_ptr<Object3D> &object, const std::shared_ptr<Camera>& camera);
};

#endif //DGF_GRAPHICS_CORE_RENDERER_H
