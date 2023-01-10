//
// Created by ivan on 7.1.2023..
//

#ifndef OPENGL_EXAMPLES_MESH_H
#define OPENGL_EXAMPLES_MESH_H

#include "Object3D.h"
#include "Geometry.h"
#include "Material.h"
#include <glad/glad.h>
#include <string>

class Mesh : public Object3D {
public:
    Geometry geometry;
    Material material;
    // should this object be rendered?
    bool visible;
    // vertex array object reference
    GLuint vaoRef;

    Mesh(Geometry g, Material m) {
        geometry = g;
        material = m;
        visible = true;

        // set up associations between
        // attributes stored in geometry
        // and shader program stored in material
        glGenVertexArrays(1, &vaoRef);
        glBindVertexArray(vaoRef);

        for (const auto myPair: geometry.attributes) {
            std::string variableName = myPair.first;
            Attribute attribute = geometry.attributes[variableName];
            attribute.associateVariable(material.programRef, variableName);
        }

        // unbind this vertex array object
        glBindVertexArray(0);
    }
};

#endif //OPENGL_EXAMPLES_MESH_H
