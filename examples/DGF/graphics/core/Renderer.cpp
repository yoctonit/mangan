#include <glad/glad.h>
#include "Renderer.h"


void Renderer::initialize() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    // support transparency
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // required for antialiasing
    glEnable(GL_MULTISAMPLE);
}

void Renderer::setClearColor(glm::vec3 color) {
    glClearColor(color.r, color.g, color.b, 1);
}

void Renderer::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void Renderer::render(const std::shared_ptr<Object3D> &scene, const std::shared_ptr<Camera> &camera) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->updateViewMatrix();

    // extract list of all objects in scene
    std::vector<std::shared_ptr<Object3D>> descendentList = scene->getDescendentList();

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

        // update uniforms stored in material
        for (auto &[key, val]: object->material()->uniforms()) {
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