//
// Created by ivan on 2.5.2020..
//

#ifndef INCLUDED_VERTEX_NORMAL_MODEL_H
#define INCLUDED_VERTEX_NORMAL_MODEL_H

#include <vector>
#include "glm/vec3.hpp"

namespace mn {

    class vertex_normal_model {

    public:
        vertex_normal_model() = default;
        virtual ~vertex_normal_model() = default;

        [[nodiscard]] virtual const std::vector<glm::vec3>& vertices() const = 0;
        [[nodiscard]] virtual const std::vector<glm::vec3>& normals() const = 0;
        [[nodiscard]] virtual int number_of_vertices() const = 0;

    };

}

#endif // INCLUDED_VERTEX_NORMAL_MODEL_H
