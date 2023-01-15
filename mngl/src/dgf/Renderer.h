//
// Created by ivan on 8.1.2023..
//

#ifndef INCLUDED_MN_RENDERER_H
#define INCLUDED_MN_RENDERER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
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
        glEnable(GL_MULTISAMPLE); // required for antialiasing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void setClearColor(glm::vec3 color) {
        glClearColor(color.r, color.g, color.b, 1.0f);
    }

    void render(Scene &scene, Camera &camera) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.updateViewMatrix();

        std::list<std::shared_ptr<Object3D>> descendentList = scene.getDescendentList();
        for (const std::shared_ptr<Object3D> &obj: descendentList) {
            obj->draw(camera);
        }
    }
};

#endif //INCLUDED_MN_RENDERER_H

//        std::list<std::shared_ptr<Mesh>> meshList;
//        for (const std::shared_ptr<Object3D> &obj: descendentList)
//            if (obj->isMesh())
//                meshList.push_back(std::dynamic_pointer_cast<Mesh>(obj));
//        for (const std::shared_ptr<Mesh> &mesh: meshList) {
//        }

//// if this object is not visible,
//// continue to next object in list
//if (!mesh->visible)
//continue;
//
//glUseProgram(mesh->material->programRef);
//// bind VAO
//glBindVertexArray(mesh->vaoRef);
//// update uniform values stored outside of material
//Mn::Shader::UploadUniform(mesh->material->uniforms["modelMatrix"], mesh->getWorldMatrix());
//Mn::Shader::UploadUniform(mesh->material->uniforms["viewMatrix"], camera.viewMatrix);
//Mn::Shader::UploadUniform(mesh->material->uniforms["projectionMatrix"], camera.projectionMatrix);
////            mesh->material.uniforms["modelMatrix"]->value() = mesh->getWorldMatrix();
////            mesh->material.uniforms["viewMatrix"]->value() = camera.viewMatrix;
////            mesh->material.uniforms["projectionMatrix"]->value() = camera.projectionMatrix;
//
//// update uniforms stored in material
////            for (Uniform uniform: mesh->material.uniforms.values())
////                uniform->upload();
//mesh->material->uploadUniforms();
//
//// update render settings
//for (const auto &myPair: mesh->material->renderSettings) {
//std::string variableName = myPair.first;
//myPair.second.apply();
//}
//
//glDrawArrays(mesh->material->drawStyle, 0, mesh->geometry->vertexCount);
