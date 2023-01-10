//
// Created by ivan on 29.4.2020..
//

#include "icosahedron.h"
#include <vector>
#include <glm/glm.hpp>

namespace mn {

    void icosahedron::create(float r, int lor, glm::vec4 c) {
        _radius = r;
        _level_of_recursion = lor;
        _color = c;
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
        _scale = 1.0f;

        _name = "ICOSAHEDRON_100"; // generate name from lor and radius

        const float X = .525731112119133606;
        const float Z = .850650808352039932;

        // 12 vertices of unit icosahedron
        std::vector<glm::vec3> base_vertices{
            glm::vec3(-X, 0.0f, Z), glm::vec3(X, 0.0f, Z), glm::vec3(-X, 0.0f, -Z),
            glm::vec3(X, 0.0f, -Z), glm::vec3(0.0f, Z, X), glm::vec3(0.0f, Z, -X),
            glm::vec3(0.0f, -Z, X), glm::vec3(0.0f, -Z, -X), glm::vec3(Z, X, 0.0f),
            glm::vec3(-Z, X, 0.0f), glm::vec3(Z, -X, 0.0f), glm::vec3(-Z, -X, 0.0f)
        };

        // indices of vertices, grouped by 3
        // that is, every 3 indices mark 1 triangle
        std::vector<int> indices{
            1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4, 1, 8, 4,
            1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
            3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0,
            10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
        };

        // For each face of icosahedron (20 faces * 3 vertices per face)
        // for (int i = 0; i < 60; i += 3) {
        for (int i = 0; i < 60; i += 3) {
            _subdivide(
                    base_vertices[indices[i + 0]],
                    base_vertices[indices[i + 1]],
                    base_vertices[indices[i + 2]],
                    _level_of_recursion
            );
        }
    }

    void icosahedron::_subdivide(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int lor) {
        if (lor == 0) {
            _vertices.push_back(v1);
            _vertices.push_back(v2);
            _vertices.push_back(v3);

//            _normals.push_back(glm::normalize(v1));
//            _normals.push_back(glm::normalize(v2));
//            _normals.push_back(glm::normalize(v3));

            _normals.push_back(v1);
            _normals.push_back(v2);
            _normals.push_back(v3);

            return;
        }

        glm::vec3 v12 = glm::normalize(0.5f * (v1 + v2));
        glm::vec3 v23 = glm::normalize(0.5f * (v2 + v3));
        glm::vec3 v31 = glm::normalize(0.5f * (v3 + v1));

        // vec3.scale(v12, v12, this.radius);
        // vec3.scale(v23, v23, this.radius);
        // vec3.scale(v31, v31, this.radius);

        _subdivide(v1, v12, v31, lor-1);
        _subdivide(v2, v23, v12, lor-1);
        _subdivide(v3, v31, v23, lor-1);
        _subdivide(v12, v23, v31, lor-1);
    }

}
