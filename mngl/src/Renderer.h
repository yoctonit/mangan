//
// Created by ivan on 8.1.2023..
//

#ifndef OPENGL_EXAMPLES_RENDERER_H
#define OPENGL_EXAMPLES_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <list>
#include <memory>
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Uniform.h"

class Renderer {
public:
    Renderer() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        // required for antialiasing
        glEnable(GL_MULTISAMPLE);
    }

    void setClearColor(glm::vec3 color) {
        glClearColor(color.r, color.g, color.b, 1.0f);
    }

    void render(Scene scene, Camera camera) const {
        // clear color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // update camera view (calculate inverse)
        camera.updateViewMatrix();
        
        // extract list of all Mesh objects in scene
        std::list<std::shared_ptr<Object3D>> descendentList = scene.getDescendentList();
        std::list<std::shared_ptr<Mesh>> meshList;
        for (const std::shared_ptr<Object3D>& obj: descendentList)
//            if (typeid(obj) == typeid(Mesh))
//                meshList.push_back(std::static_pointer_cast<std::shared_ptr<Mesh>>(obj));
            for (const std::shared_ptr<Mesh>& mesh: meshList) {
            // if this object is not visible,
            // continue to next object in list
            if (!mesh->visible)
                continue;

            glUseProgram(mesh->material.programRef);
            // bind VAO
            glBindVertexArray(mesh->vaoRef);
            // update uniform values stored outside of material
            Mn::Shader::UploadUniform(mesh->material.uniforms["modelMatrix"], mesh->getWorldMatrix());
            Mn::Shader::UploadUniform(mesh->material.uniforms["viewMatrix"], camera.viewMatrix);
            Mn::Shader::UploadUniform(mesh->material.uniforms["projectionMatrix"], camera.projectionMatrix);
//            mesh->material.uniforms["modelMatrix"]->value() = mesh->getWorldMatrix();
//            mesh->material.uniforms["viewMatrix"]->value() = camera.viewMatrix;
//            mesh->material.uniforms["projectionMatrix"]->value() = camera.projectionMatrix;

            // update uniforms stored in material
//            for (Uniform uniform: mesh->material.uniforms.values())
//                uniform->upload();

            // update render settings
//            for (RenderSetting setting: mesh.material.renderSettings.values())
//                setting.apply();

            glDrawArrays(mesh->material.drawStyle, 0, mesh->geometry.vertexCount);
        }
    }
};

#endif //OPENGL_EXAMPLES_RENDERER_H
