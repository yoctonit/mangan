#include "Shadow.h"
#include "../material/DepthMaterial.h"


Shadow::Shadow(std::shared_ptr<DirectionalLight> ls, float s, glm::vec2 resolution, float b) {
    lightSource = ls;
    camera = std::make_shared<Camera>();
    setCameraBounds(-5, 5, -5, 5, 0, 20);
    // lightSource->add( camera );

    renderTarget = std::make_shared<RenderTarget>(resolution.x, resolution.y, GL_NEAREST, GL_NEAREST,
                                                  GL_CLAMP_TO_BORDER);
    material = std::make_shared<DepthMaterial>();
    strength = s;
    bias = b;
}

Shadow::Shadow(std::shared_ptr<DirectionalLight> ls)
        : Shadow(ls, 0.5f, glm::vec2(512, 512), 0.01f) {}

void Shadow::setCameraBounds(
        float left, float right,
        float bottom, float top,
        float near, float far) {
    camera->setOrthographic(left, right, bottom, top, near, far);
}

void Shadow::updateInternal() {
    camera->updateViewMatrix();
    material->uniforms()["viewMatrix"].data().m_dataMat4x4 = camera->viewMatrix();
    material->uniforms()["projectionMatrix"].data().m_dataMat4x4 = camera->projectionMatrix();
}

//std::map<std::string, Uniform> &Shadow::uniforms() {
//    return m_uniforms;
//}
