//
// Created by ivan on 7.1.2023..
//

#ifndef INCLUDED_MN_MESH_H
#define INCLUDED_MN_MESH_H

#include "Object3D.h"
#include "geometry/Geometry.h"
#include "material/Material.h"
#include <glad/glad.h>
#include <string>
#include <utility>

class Mesh : public Object3D {
public:
    Geometry geometry;
    Material material;
    // should this object be rendered?
    bool visible;
    // vertex array object reference
    GLuint vaoRef{};

    bool isMesh() const override { return true; }

//    Mesh () = default;
    Mesh(Geometry g, Material m) : geometry(std::move(g)), material(std::move(m)) {
//        geometry = g;
//        material = m;
        visible = true;

        // set up associations between
        // attributes stored in geometry
        // and shader program stored in material
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        for (const auto &myPair: geometry.attributes) {
//            std::string variableName = myPair.first;
//            std::shared_ptr<Mn::Shader::Attribute> attribute = geometry.attributes[variableName];
//            attribute->associateVariable(material.programRef, variableName);
            myPair.second->associateVariable(material.programRef, myPair.first);
        }

        // unbind this vertex array object
        glBindVertexArray(0);
    }
};

#endif //INCLUDED_MN_MESH_H
