#include <glad/glad.h>
#include "Renderer.h"


Renderer::Renderer()
        : clearColorBuffer{true}, clearDepthBuffer{true}, renderTarget{nullptr} {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // support depth testing
    glEnable(GL_DEPTH_TEST);

    // support transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // required for antialiasing
    glEnable(GL_MULTISAMPLE);

    // scenes support 4 lights; precisely 4 must be present
    light0 = std::make_shared<Light>();
    light1 = std::make_shared<Light>();
    light2 = std::make_shared<Light>();
    light3 = std::make_shared<Light>();
}

void Renderer::setClearColor(glm::vec3 color) {
    glClearColor(color.r, color.g, color.b, 1);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::setDimensions(int w, int h) {
    width = w;
    height = h;
}

void Renderer::render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera) {
    // activate render target
    if (renderTarget == nullptr) {
        // set render target to window
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, width, height); // TODO: set correctly...
    } else {
        // set render target properties
        glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->framebufferRef);
        glViewport(0, 0, renderTarget->width, renderTarget->height);
    }

    // clear color and/or depth buffers
    if (clearColorBuffer)
        glClear(GL_COLOR_BUFFER_BIT);
    if (clearDepthBuffer)
        glClear(GL_DEPTH_BUFFER_BIT);

    camera->updateViewMatrix();

    // extract list of all objects in scene
    std::vector<std::shared_ptr<Object3D>> descendentList = scene->getDescendentList();

//    // scenes support 4 lights; precisely 4 must be present
//    light0 = std::make_shared<Light>();
//    light1 = std::make_shared<Light>();
//    light2 = std::make_shared<Light>();
//    light3 = std::make_shared<Light>();

    for (const auto &object: descendentList) {
        // if this object is not mesh, continue to next object in list
        if (!object->isMesh()) continue;

        // if this (mesh) object is not visible, continue to next object in list
        if (!object->isVisible()) continue;

        glUseProgram(object->material()->programRef());

        // bind VAO
        glBindVertexArray(object->vaoRef());

        // update uniform values stored outside of material
        object->material()->uniforms()["modelMatrix"].data().m_dataMat4x4 = object->getWorldMatrix();
        object->material()->uniforms()["viewMatrix"].data().m_dataMat4x4 = camera->viewMatrix();
        object->material()->uniforms()["projectionMatrix"].data().m_dataMat4x4 = camera->projectionMatrix();

        // if material uses light data, add lights from list
        if (object->material()->usesLight()) {
            light0->setUniforms(object->material()->programRef(), 0);
            light1->setUniforms(object->material()->programRef(), 1);
            light2->setUniforms(object->material()->programRef(), 2);
            light3->setUniforms(object->material()->programRef(), 3);
        }
        // add camera position if needed (specular lighting)
        if (object->material()->containsUniform("viewPosition")) {
            object->material()->uniforms()["viewPosition"].data().m_dataVec3 = camera->getPosition();
        }

        // update uniforms stored in material
        for (auto &[key, val]: object->material()->uniforms()) {
            val.upload();
        }

        // update uniforms stored in lights
        for (auto &[key, val]: light0->uniforms()) {
            val.upload();
        }
        for (auto &[key, val]: light1->uniforms()) {
            val.upload();
        }
        for (auto &[key, val]: light2->uniforms()) {
            val.upload();
        }
        for (auto &[key, val]: light3->uniforms()) {
            val.upload();
        }

        // update render settings
        object->material()->renderSettings().apply();

        glDrawArrays(object->material()->drawStyle(), 0, object->geometry()->vertexCount());
    }
}

/*
void Renderer::render1(const std::shared_ptr<Object3D> &object, const std::shared_ptr<Camera> &camera) {
//    std::cout << "render called\n";
    // clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update camera view (calculate inverse)
    // camera->updateViewMatrix();

    // if this object is not mesh, continue to next object in list
    if (!object->isMesh()) return;

    // if this object is not visible, continue to next object in list
    if (!object->isVisible()) return;

    glUseProgram(object->material()->programRef());

    // bind VAO
    glBindVertexArray(object->vaoRef());

    // update uniform values stored outside of material
    object->material()->uniforms()["modelMatrix"].data().m_dataMat4x4 = object->getWorldMatrix();
    object->material()->uniforms()["viewMatrix"].data().m_dataMat4x4 = camera->viewMatrix();
    object->material()->uniforms()["projectionMatrix"].data().m_dataMat4x4 = camera->projectionMatrix();

    // update uniforms stored in material
    for (auto &[key, val]: object->material()->uniforms()) {
        val.upload();
    }

    // update render settings
    for (auto &setting: object->material()->renderSettings()) {
        setting->apply();
    }
//    std::cout << "object->material()->drawStyle() " << object->material()->drawStyle() << "\n";
//    std::cout << "GL_TRIANGLES " << GL_TRIANGLES << "\n";
//    std::cout << "object->geometry()->vertexCount() " << object->geometry()->vertexCount() << "\n";

    glDrawArrays(object->material()->drawStyle(), 0, object->geometry()->vertexCount());
//    std::cout << "render finished\n\n";
}
*/