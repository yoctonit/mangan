//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_MESH_H
#define INCLUDED_MN_MESH_H

#include "Object3D.h"
#include "Camera.h"
#include "dgf/geometry/Geometry.h"
#include "dgf/material/Material.h"
#include "glad/glad.h"
#include <string>
#include <utility>

class Mesh : public Object3D {
public:
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;
    // should this object be rendered?
    bool visible;
    // vertex array object reference
    GLuint vaoRef{};

//    bool isMesh() const override { return true; }

//    Mesh () = default;
    Mesh(std::shared_ptr<Geometry> g, std::shared_ptr<Material> m)
            : geometry(g), material(m) {
        visible = true;

        // set up associations between
        // attributes stored in geometry
        // and shader program stored in material
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        for (const auto &myPair: geometry->attributes) {
//            std::string variableName = myPair.first;
//            std::shared_ptr<Mn::Shader::Attribute> attribute = geometry.attributes[variableName];
//            attribute->associateVariable(material.programRef, variableName);
            myPair.second->associateVariable(material->programRef, myPair.first);
        }

        // unbind this vertex array object
        glBindVertexArray(0);
    }

    void draw(const Camera & camera) const override {
        if (!visible)
            return;

        glUseProgram(material->programRef);
        // bind VAO
        glBindVertexArray(vaoRef);
        // update uniform values stored outside of material
        material->uniforms["modelMatrix"].upload(getWorldMatrix());
        material->uniforms["viewMatrix"].upload(camera.viewMatrix);
        material->uniforms["projectionMatrix"].upload(camera.projectionMatrix);
//        Mn::Shader::UploadUniform(material->uniforms["modelMatrix"], getWorldMatrix());
//        Mn::Shader::UploadUniform(material->uniforms["viewMatrix"], camera.viewMatrix);
//        Mn::Shader::UploadUniform(material->uniforms["projectionMatrix"], camera.projectionMatrix);

        // update uniforms stored in material
        //    for (Uniform uniform: mesh->material.uniforms.values())
        //        uniform->upload();
        material->uploadUniforms();

        // update render settings
        for (const auto &myPair: material->renderSettings) {
            std::string variableName = myPair.first;
            myPair.second.apply();
        }

        glDrawArrays(material->drawStyle, 0, geometry->vertexCount);
    }
};

#endif //INCLUDED_MN_MESH_H
