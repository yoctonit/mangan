#include <glad/glad.h>
#include "Renderer.h"
#include "../material/DepthMaterial.h"


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
    clearColor = glm::vec4(color, 1.0f);
    glClearColor(color.r, color.g, color.b, 1.0f);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    clearColor = glm::vec4(r, g, b, a);
    glClearColor(r, g, b, a);
}

void Renderer::setDimensions(int w, int h) {
    width = w;
    height = h;
}

void Renderer::render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera) {
    // extract list of all objects in scene
    std::vector<std::shared_ptr<Object3D>> descendentList = scene->getDescendentList();

    // shadow pass start ----------------------------

    if (shadowsEnabled) {
        // set render target properties
        glBindFramebuffer(GL_FRAMEBUFFER, shadowObject->renderTarget->framebufferRef);
        glViewport(0, 0, shadowObject->renderTarget->width, shadowObject->renderTarget->height);

        // set default color to white, used when no objects present to cast shadows
        glClearColor(1, 1, 1, 1);

        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        // reset original clear color
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

        // everything in the scene gets rendered with depthMaterial
        //   so only need to call glUseProgram & set matrices once
        glUseProgram(shadowObject->material->programRef());

        shadowObject->updateInternal();

        for (const auto &object: descendentList) {
            // if this object is not mesh, continue to next object in list
            if (!object->isMesh()) continue;

            // if this (mesh) object is not visible, continue to next object in list
            if (!object->isVisible()) continue;

            // only triangle-based meshes cast shadows
            if (object->material()->drawStyle() != GL_TRIANGLES) continue;

            glUseProgram(object->material()->programRef());

            // bind VAO
            glBindVertexArray(object->vaoRef());

            // update transform data
            shadowObject->material->uniforms()["modelMatrix"].data().m_dataMat4x4 = object->getWorldMatrix();

            // update uniforms (matrix data) stored in shadow material
            for (auto &[key, val]: shadowObject->material->uniforms()) {
                val.upload();
            }

            // no render settings to update

            glDrawArrays(GL_TRIANGLES, 0, object->geometry()->vertexCount());
        }
    }

    // shadow pass end ----------------------------

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

        // add shadow data if enabled and used by shader
        if (shadowsEnabled && object->material()->containsUniform("shadow0.lightDirection")) {
            object->material()->setShadowUniform("shadow0", shadowObject);
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

void Renderer::enableShadows(
        const std::shared_ptr<DirectionalLight> &shadowLight,
        float strength, glm::vec2 resolution, float bias) {
    shadowsEnabled = true;
    shadowObject = std::make_shared<Shadow>(shadowLight, strength, resolution, bias);
}

void Renderer::enableShadows(const std::shared_ptr<DirectionalLight> &shadowLight) {
    enableShadows(shadowLight, 0.5f, glm::vec2(512, 512), 0.01f);
}
