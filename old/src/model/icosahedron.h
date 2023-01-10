//
// Created by ivan on 29.4.2020..
//

#ifndef INCLUDED_ICOSAHEDRON_H
#define INCLUDED_ICOSAHEDRON_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <vector>
#include <cmath>
#include <string>
// #include "vertex_normal_model.h"
#include "model.h"

namespace mn {

    class icosahedron : public model {
    public:
        icosahedron() = default;

        void create(float r, int lor, glm::vec4 c);

        void position(glm::vec3 position_) { _position = position_; }
        [[nodiscard]] glm::vec3 position() const { return _position; }

        void scale(float scale_) { _scale = scale_; }
        [[nodiscard]] float scale() const { return _scale; }

        void color(glm::vec4 c) { _color = c; }
        [[nodiscard]] glm::vec4 color() const { return _color; }

        [[nodiscard]] const std::vector<glm::vec3>& vertices() const override { return _vertices; }
        [[nodiscard]] const std::vector<glm::vec3>& normals() const override { return _normals; }
        [[nodiscard]] int number_of_vertices() const override {
            // 20 faces divided to 4 faces _level_of_recursion times, times 3 vertices
            return 20 * static_cast<int>(std::pow(4, _level_of_recursion)) * 3;
        }
        [[nodiscard]] std::string name() const override { return _name; }
        void override_name(const std::string& name_) { _name = name_; }

        [[nodiscard]] glm::mat4 transform() const override {
            glm::mat4 m = glm::translate(_position) * glm::scale(glm::vec3(_scale, _scale, _scale));
            return m;
        };

    private:
        float _radius;
        int _level_of_recursion;
        glm::vec4 _color;

        glm::vec3 _position;
        float _scale;

        std::vector<glm::vec3> _vertices;
        std::vector<glm::vec3> _normals;
        std::string _name;

        void _subdivide(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int lor);
    };

}

#endif //INCLUDED_ICOSAHEDRON_H
