#include "Postprocessor.h"
#include "../core/Mesh.h"

#include <utility>


Postprocessor::Postprocessor(std::shared_ptr<Renderer> r,
                             const std::shared_ptr<Object3D> &s,
                             const std::shared_ptr<Camera> &c,
                             const std::shared_ptr<RenderTarget> &rt
) {
    renderer = std::move(r);
    sceneList.push_back(s);
    cameraList.push_back(c);
    renderTargetList.push_back(rt);

    finalRenderTarget = rt;

    m_orthoCamera = std::make_shared<Camera>();
    // aligned with clip space by default
    m_orthoCamera->setOrthographic(-1, 1, -1, 1, 1, -1);

    // generate a rectangle already aligned with clip space;
    // no matrix transformations will be applied
    m_rectangleGeom = std::make_shared<Geometry>();

    glm::vec2 P0(-1.0f, -1.0f);
    glm::vec2 P1(1.0f, -1.0f);
    glm::vec2 P2(-1.0f, 1.0f);
    glm::vec2 P3(1.0f, 1.0f);

    glm::vec2 T0(0.0f, 0.0f);
    glm::vec2 T1(1.0f, 0.0f);
    glm::vec2 T2(0.0f, 1.0f);
    glm::vec2 T3(1.0f, 1.0f);


    std::vector<glm::vec2> positionList{P0, P1, P3, P0, P3, P2};
    std::vector<GLfloat> positionData = Geometry::flatten(positionList);

    std::vector<glm::vec2> uvList{T0, T1, T3, T0, T3, T2};
    std::vector<GLfloat> uvData = Geometry::flatten(uvList);

    m_rectangleGeom->addAttribute("vertexPosition", Attribute::Type::Vec2, positionData);
    m_rectangleGeom->addAttribute("vertexUV", Attribute::Type::Vec2, uvData);
    m_rectangleGeom->vertexCount(6);
}

void Postprocessor::addEffect(const std::shared_ptr<Material> &effect) {
    std::shared_ptr<Scene> postScene = std::make_shared<Scene>();
    std::shared_ptr<RenderTarget> target = std::make_shared<RenderTarget>(800,
                                                                          600); // Base.windowWidth, Base.windowHeight);

    // change the previous entry in the render target list
    // to this newly created render target
    auto size = renderTargetList.size();
//    renderTargetList.set(size - 1, target);
    renderTargetList[size - 1] = target;
    // the effect in this render pass will use
    // the texture that was written to in the previous render pass
    effect->uniforms()["tex"].data().m_dataVec2 = glm::vec2(target->texture->textureRef(), 1);
    auto mesh = std::make_shared<Mesh>("mesh", m_rectangleGeom, effect);
    postScene->add(mesh);

    sceneList.push_back(postScene);
    cameraList.push_back(m_orthoCamera);
    renderTargetList.push_back(finalRenderTarget);
}

void Postprocessor::render() {
    auto passes = sceneList.size();
    for (int n = 0; n < passes; n++) {
        renderer->renderTarget = renderTargetList[n];
        renderer->render(sceneList[n], cameraList[n]);
    }
}
